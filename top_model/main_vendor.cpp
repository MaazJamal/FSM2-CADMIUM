//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

#include "../atomics/moore.h"
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs


#include <iostream>
#include <NDTime.hpp>

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

// Input ports
struct input_port : public cadmium::in_port<Message_t>{};

// output ports
struct output_port : public cadmium::out_port<Message_t>{};

/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_Message_t : public iestream_input<Message_t,T> {
    public:
        InputReader_Message_t () = default;
        InputReader_Message_t (const char* file_path) : iestream_input<Message_t,T>(file_path) {}
};


int main(){

 /****** Input Readers atomic model instantiation *******************/
    const char * i_input_data_control = "../input_data/main_vendor.txt";
    shared_ptr<dynamic::modeling::model> input_reader = dynamic::translate::make_dynamic_atomic_model<InputReader_Message_t, TIME, const char* >("input_reader" , std::move(i_input_data_control));



 /****** Moore atomic model instantiation *******************/
  shared_ptr<dynamic::modeling::model> zero = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("zero", true,0,0,vector<pair<int,int>>{make_pair(0,1),make_pair(1,2)});
  shared_ptr<dynamic::modeling::model> five = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("five", false,1,5,vector<pair<int,int>>{make_pair(0,2),make_pair(1,3)});
  shared_ptr<dynamic::modeling::model> ten = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("ten", false,2,10,vector<pair<int,int>>{make_pair(0,3),make_pair(1,4)});
  shared_ptr<dynamic::modeling::model> fifteen = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("fifteen", false,3,15,vector<pair<int,int>>{make_pair(0,4),make_pair(1,4), make_pair(2,0)});
  shared_ptr<dynamic::modeling::model> twenty = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("twenty", false,4,20,vector<pair<int,int>>{make_pair(3,0)});
   
//    shared_ptr<dynamic::modeling::model> state0 = dynamic::translate::make_dynamic_atomic_model<Moore, TIME>("state0");

/*******TOP MODEL********/
    dynamic::modeling::Ports iports_TOP = {};
    dynamic::modeling::Ports oports_TOP = {typeid(output_port)};
    dynamic::modeling::Models submodels_TOP = {input_reader, zero, five, ten, fifteen, twenty};
    dynamic::modeling::EICs eics_TOP = {};
    dynamic::modeling::EOCs eocs_TOP = {
        dynamic::translate::make_EOC<Moore_defs::state_out,output_port>("zero"),
        dynamic::translate::make_EOC<Moore_defs::error_out,output_port>("zero"),
        dynamic::translate::make_EOC<Moore_defs::state_out,output_port>("five"),
        dynamic::translate::make_EOC<Moore_defs::error_out,output_port>("five"),
        dynamic::translate::make_EOC<Moore_defs::state_out,output_port>("ten"),
        dynamic::translate::make_EOC<Moore_defs::error_out,output_port>("ten"),
        dynamic::translate::make_EOC<Moore_defs::state_out,output_port>("fifteen"),
        dynamic::translate::make_EOC<Moore_defs::error_out,output_port>("fifteen"),
        dynamic::translate::make_EOC<Moore_defs::state_out,output_port>("twenty"),
        dynamic::translate::make_EOC<Moore_defs::error_out,output_port>("twenty"),
    };
    dynamic::modeling::ICs ics_TOP = {
        dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Moore_defs::event_in>("input_reader","zero"),
        dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Moore_defs::event_in>("input_reader","five"),
        dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Moore_defs::event_in>("input_reader","ten"),
        dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Moore_defs::event_in>("input_reader","fifteen"),
        dynamic::translate::make_IC<iestream_input_defs<Message_t>::out,Moore_defs::event_in>("input_reader","twenty"),
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("zero","five"), // can go from zero to five 
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("zero","ten"), // or ten
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("five","ten"),  // 5 to 10
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("five","fifteen"), 
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("ten","fifteen"), //ten to fifteen 
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("ten","twenty"),
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("fifteen","twenty"),  // get to 20c candy
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("fifteen","zero"), // get 15c cabdy
        dynamic::translate::make_IC<Moore_defs::transition_out,Moore_defs::transition_in>("twenty","zero")  // get 20c candy
    };
    shared_ptr<dynamic::modeling::coupled<TIME>> TOP;
    TOP = make_shared<dynamic::modeling::coupled<TIME>>(
        "TOP", submodels_TOP, iports_TOP, oports_TOP, eics_TOP, eocs_TOP, ics_TOP 
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/COUPLED_VENDOR_outputs.txt");
    struct oss_sink_messages{
        static ostream& sink(){          
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/COUPLED_VENDOR_state.txt");
    struct oss_sink_state{
        static ostream& sink(){          
            return out_state;
        }
    };

    using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;

    using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;

    /************** Runner call ************************/ 
    dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
    r.run_until(NDTime("00:00:00:135"));
    return 0;

}