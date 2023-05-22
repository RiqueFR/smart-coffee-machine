#include "esphome.h"
#include <string>
#include "coffee.h"

//using namespace esphome;

class MyCustomTextSensor : public PollingComponent, public TextSensor {
 private:
  std::string val;

 public:
  // constructor
  MyCustomTextSensor() : PollingComponent(1000) {}

  std::string get_val() {
	  return this->val;
  }

  void setup() override {
	// This will be called by App.setup()
  }
  void update() override {
	// This will be called every "update_interval" milliseconds.
	//publish_state(this->val);
	publish_state(this->val);
  }
  void receive_value(std::string val) {
	  //this->val = val;
      this->val = val;
  }
};

class MyCustomComponent : public PollingComponent {
 public:
  MyCustomTextSensor *custom_sensor = new MyCustomTextSensor();
  Coffee coffee = Coffee(30);

  int count = 0;

  MyCustomComponent() : PollingComponent(1000) { }

  void setup() override {
    pinMode(2, OUTPUT);
    coffee.setup();
  }

  void loop() override {
    coffee.loop();
  }

  void update() override {
    // This is the actual sensor reading logic.
	//ESP_LOGD("custom", "sensor %d", custom_sensor->get_val());
    //if(count%2)
      //custom_sensor->receive_value("Hello World");
    //else
      //custom_sensor->receive_value("Hello Henrique");

    //count++;
    int coffeeStatus = coffee.getStatus();
	if(coffeeStatus == 1)
		custom_sensor->receive_value("Idle");
	else if(coffeeStatus == 2)
		custom_sensor->receive_value("Filling");
    else
		custom_sensor->receive_value("Draining");
  }

  void set_level(int val) {
	ESP_LOGD("custom", "cups %d", val);
    coffee.setRequestCup(val);
    //if(val % 2)
      //digitalWrite(2, 1);
    //else 
      //digitalWrite(2, 0);
  }
};
