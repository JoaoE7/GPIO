#include <string>

class Pin {
  
    public:
        Pin(std::string _name, std::string _direction, int _value);
        ~Pin();
        std::string getName();
        void setValue(int _value);
        int getValue();
        void setDirection(std::string _direction);
        std::string getDirection();
        
    private:
        std::string name;
        void pin_export();
        void pin_unexport();
};