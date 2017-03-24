#include "Pin.h"
#include <iostream>
#include <unordered_map>    
#include <cstdlib>
#include <fstream>
#include <string>

extern std::unordered_map<std::string,std::string> map_pins;

Pin::Pin(std::string _name, std::string _direction, int _value) {
    if ( (map_pins.find(_name) != map_pins.end()) && ((_direction == "in") || (_direction == "out")) && ((_value == 1) || (_value == 0)) ) {
        name = _name;
        pin_export();
        setDirection(_direction);
        setValue(_value);
    } else {
        throw std::invalid_argument("Name, direction or value invalid");
    }
}

Pin::~Pin() {
    pin_unexport();
}

void Pin::pin_export() {
    std::string numero;
    std::ofstream myfile("/sys/class/gpio/export");
    if (myfile.is_open()) {
        std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
        numero = it->second;
        myfile << numero;
        myfile.close();
    } else {
        throw std::logic_error("Could not open file");
    }
}

void Pin::pin_unexport () {
    std::string numero;
    std::ofstream myfile("/sys/class/gpio/unexport");
    if (myfile.is_open()) {
        std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
        numero = it->second;
        myfile << numero;
        myfile.close();
    } else {
        throw std::logic_error("Could not open file");
    }
}

std::string Pin::getName() {
    return name;
}

void Pin::setValue(int _value) {
        std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
        std::ofstream myfile("/sys/class/gpio/gpio" + it->second  + "/value");
        if (myfile.is_open()) {
            myfile << _value;
            myfile.close();
        } else {
            throw std::logic_error("Could not open file");
        }
}

int Pin::getValue() {
    std::string s_value = "";
    int value;
    std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
    std::string caminho = "/sys/class/gpio/gpio" +  it->second + "/value";
    std::ifstream myfile(caminho);
    if (myfile.is_open()) {
        getline(myfile,s_value);
        value = atoi(s_value.c_str());
        myfile.close();
        return value;
    } else {
        throw std::logic_error("Could not open file");
    }
}
    
void Pin::setDirection(std::string _direction) {
        std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
        std::ofstream myfile("/sys/class/gpio/gpio" + it->second + "/direction");
        if (myfile.is_open()) {
            myfile << _direction;
            myfile.close();
        } else {
            throw std::logic_error("Could not open file");
        }
}

std::string Pin::getDirection() {
    std::string direction = "";
    std::unordered_map<std::string, std::string>::const_iterator it = map_pins.find(name);
    std::ifstream myfile("/sys/class/gpio/gpio" + it->second + "/direction");
    if (myfile.is_open()) {
        myfile >> direction;
        myfile.close();
        return direction;
    } else {
        throw std::logic_error("Could not open file");
    }
}