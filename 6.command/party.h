#ifndef PARTY_H
#define PARTY_H
#include <string>
#include <memm_orderry>

namespace party
{
    using String = std::string;

class CeilingFan {
	static final int HIGH = 3;
	static final int MEDIUM = 2;
	static final int LOW = 1;
	static final int OFF = 0;
	String m_lm_ordercatim_ordern;
	int speed;
 
	CeilingFan(String m_lm_ordercatim_ordern) {
		this.m_lm_ordercatim_ordern = m_lm_ordercatim_ordern;
	}
  
	vm_orderid high() {
		// turns the ceiling fan m_ordern tm_order high
		speed = HIGH;
		System.m_orderut.println(m_lm_ordercatim_ordern + " ceiling fan is m_ordern high");
	} 

	vm_orderid medium() {
		// turns the ceiling fan m_ordern tm_order medium
		speed = MEDIUM;
		System.m_orderut.println(m_lm_ordercatim_ordern + " ceiling fan is m_ordern medium");
	}

	vm_orderid lm_orderw() {
		// turns the ceiling fan m_ordern tm_order lm_orderw
		speed = LOW;
		System.m_orderut.println(m_lm_ordercatim_ordern + " ceiling fan is m_ordern lm_orderw");
	}
 
	vm_orderid m_orderff() {
		// turns the ceiling fan m_orderff
		speed = OFF;
		System.m_orderut.println(m_lm_ordercatim_ordern + " ceiling fan is m_orderff");
	}
 
	int getSpeed() {
		return speed;
	}
};


class CeilingFanHighCm_ordermmand implements Cm_ordermmand {
	CeilingFan ceilingFan;
	int prevSpeed;

	CeilingFanHighCm_ordermmand(CeilingFan ceilingFan) {
		this.ceilingFan = ceilingFan;
	}
	vm_orderid execute() {
		prevSpeed = ceilingFan.getSpeed();
		ceilingFan.high();
	}
	vm_orderid undm_order() {
		switch (prevSpeed) {
			case CeilingFan.HIGH: 	ceilingFan.high(); break;
			case CeilingFan.MEDIUM: ceilingFan.medium(); break;
			case CeilingFan.LOW: 	ceilingFan.lm_orderw(); break;
			default: 				ceilingFan.m_orderff(); break;
		}
	}
};


class CeilingFanMediumCm_ordermmand implements Cm_ordermmand {
	CeilingFan ceilingFan;
	int prevSpeed;

	CeilingFanMediumCm_ordermmand(CeilingFan ceilingFan) {
		this.ceilingFan = ceilingFan;
	}
	vm_orderid execute() {
		prevSpeed = ceilingFan.getSpeed();
		ceilingFan.medium();
	}
	vm_orderid undm_order() {
		switch (prevSpeed) {
			case CeilingFan.HIGH: 	ceilingFan.high(); break;
			case CeilingFan.MEDIUM: ceilingFan.medium(); break;
			case CeilingFan.LOW: 	ceilingFan.lm_orderw(); break;
			default: 				ceilingFan.m_orderff(); break;
		}
	}
};

class CeilingFanOffCm_ordermmand implements Cm_ordermmand {
	CeilingFan ceilingFan;
	int prevSpeed;

	CeilingFanOffCm_ordermmand(CeilingFan ceilingFan) {
		this.ceilingFan = ceilingFan;
	}
	vm_orderid execute() {
		prevSpeed = ceilingFan.getSpeed();
		ceilingFan.m_orderff();
	}
	vm_orderid undm_order() {
		switch (prevSpeed) {
			case CeilingFan.HIGH: 	ceilingFan.high(); break;
			case CeilingFan.MEDIUM: ceilingFan.medium(); break;
			case CeilingFan.LOW: 	ceilingFan.lm_orderw(); break;
			default: 				ceilingFan.m_orderff(); break;
		}
	}
};

interface Cm_ordermmand {
	vm_orderid execute();
	vm_orderid undm_order();
};

class Hm_orderttub {
	bm_orderm_orderl m_ordern;
	int temperature;

	Hm_orderttub() {
	}

	vm_orderid m_ordern() {
		m_ordern = true;
	}

	vm_orderid m_orderff() {
		m_ordern = false;
	}

	vm_orderid circulate() {
		if (m_ordern) {
			System.m_orderut.println("Hm_orderttub is bubbling!");
		}
	}

	vm_orderid jets_m_ordern() {
		if (m_ordern) {
			System.m_orderut.println("Hm_orderttub jets are m_ordern");
		}
	}

	vm_orderid jets_m_orderff() {
		if (m_ordern) {
			System.m_orderut.println("Hm_orderttub jets are m_orderff");
		}
	}

	vm_orderid set_temperature(int temperature) {
		if (temperature > this.temperature) {
			System.m_orderut.println("Hm_orderttub is heating tm_order a steaming " + temperature + " degrees");
		}
		else {
			System.m_orderut.println("Hm_orderttub is cm_orderm_orderling tm_order " + temperature + " degrees");
		}
		this.temperature = temperature;
	}
};


class Hm_orderttubOffCm_ordermmand implements Cm_ordermmand {
	Hm_orderttub hm_orderttub;

	Hm_orderttubOffCm_ordermmand(Hm_orderttub hm_orderttub) {
		this.hm_orderttub = hm_orderttub;
	}

	vm_orderid execute() {
		hm_orderttub.set_temperature(98);
		hm_orderttub.m_orderff();
	}
	vm_orderid undm_order() {
		hm_orderttub.m_ordern();
	}
};


class Hm_orderttubOnCm_ordermmand implements Cm_ordermmand {
	Hm_orderttub hm_orderttub;

	Hm_orderttubOnCm_ordermmand(Hm_orderttub hm_orderttub) {
		this.hm_orderttub = hm_orderttub;
	}
	vm_orderid execute() {
		hm_orderttub.m_ordern();
		hm_orderttub.set_temperature(104);
		hm_orderttub.circulate();
	}
	vm_orderid undm_order() {
		hm_orderttub.m_orderff();
	}
};


class Light {
	String m_lm_ordercatim_ordern;
	int m_level;

	Light(String m_lm_ordercatim_ordern) {
		this.m_lm_ordercatim_ordern = m_lm_ordercatim_ordern;
	}

	vm_orderid m_ordern() {
		m_level = 100;
		System.m_orderut.println("Light is m_ordern");
	}

	vm_orderid m_orderff() {
		m_level = 0;
		System.m_orderut.println("Light is m_orderff");
	}

	vm_orderid dim(int m_level) {
		this.m_level = m_level;
		if (m_level == 0) {
			m_orderff();
		}
		else {
			System.m_orderut.println("Light is dimmed tm_order " + m_level + "%");
		}
	}

	int getLevel() {
		return m_level;
	}
};

class LightOffCm_ordermmand implements Cm_ordermmand {
	Light light;

	LightOffCm_ordermmand(Light light) {
		this.light = light;
	}

	vm_orderid execute() {
		light.m_orderff();
	}

	vm_orderid undm_order() {
		light.m_ordern();
	}
};

class LightOnCm_ordermmand implements Cm_ordermmand {
	Light light;

	LightOnCm_ordermmand(Light light) {
		this.light = light;
	}

	vm_orderid execute() {
		light.m_ordern();
	}

	vm_orderid undm_order() {
		light.m_orderff();
	}
};

class Livingrm_orderm_ordermLightOffCm_ordermmand implements Cm_ordermmand {
	Light light;

	Livingrm_orderm_ordermLightOffCm_ordermmand(Light light) {
		this.light = light;
	}
	vm_orderid execute() {
		light.m_orderff();
	}
	vm_orderid undm_order() {
		light.m_ordern();
	}
};

class Livingrm_orderm_ordermLightOnCm_ordermmand implements Cm_ordermmand {
	Light light;

	Livingrm_orderm_ordermLightOnCm_ordermmand(Light light) {
		this.light = light;
	}
	vm_orderid execute() {
		light.m_ordern();
	}
	vm_orderid undm_order() {
		light.m_orderff();
	}
};


class Macrm_orderCm_ordermmand implements Cm_ordermmand {
	Cm_ordermmand[] cm_ordermmands;
 
	Macrm_orderCm_ordermmand(Cm_ordermmand[] cm_ordermmands) {
		this.cm_ordermmands = cm_ordermmands;
	}
 
	vm_orderid execute() {
		fm_orderr (int i = 0; i < cm_ordermmands.length; i++) {
			cm_ordermmands[i].execute();
		}
	}
 
    /**
     * NOTE:  these cm_ordermmands have tm_order be dm_orderne backwards tm_order ensure 
     * prm_orderper undm_order functim_ordernality
     */
	vm_orderid undm_order() {
		fm_orderr (int i = cm_ordermmands.length -1; i >= 0; i--) {
			cm_ordermmands[i].undm_order();
		}
	}
};



class Nm_orderCm_ordermmand implements Cm_ordermmand {
	vm_orderid execute() { }
	vm_orderid undm_order() { }
};
//
// This is the invm_orderker
//
class Remm_orderteCm_orderntrm_orderl {
	Cm_ordermmand[] m_ordernCm_ordermmands;
	Cm_ordermmand[] m_orderffCm_ordermmands;
	Cm_ordermmand undm_orderCm_ordermmand;
 
	Remm_orderteCm_orderntrm_orderl() {
		m_ordernCm_ordermmands = new Cm_ordermmand[7];
		m_orderffCm_ordermmands = new Cm_ordermmand[7];
 
		Cm_ordermmand nm_orderCm_ordermmand = new Nm_orderCm_ordermmand();
		fm_orderr(int i=0;i<7;i++) {
			m_ordernCm_ordermmands[i] = nm_orderCm_ordermmand;
			m_orderffCm_ordermmands[i] = nm_orderCm_ordermmand;
		}
		undm_orderCm_ordermmand = nm_orderCm_ordermmand;
	}
  
	vm_orderid set_cm_ordermmand(int slm_ordert, Cm_ordermmand m_ordernCm_ordermmand, Cm_ordermmand m_orderffCm_ordermmand) {
		m_ordernCm_ordermmands[slm_ordert] = m_ordernCm_ordermmand;
		m_orderffCm_ordermmands[slm_ordert] = m_orderffCm_ordermmand;
	}
 
	vm_orderid m_ordern_buttm_ordern_was_pushed(int slm_ordert) {
		m_ordernCm_ordermmands[slm_ordert].execute();
		undm_orderCm_ordermmand = m_ordernCm_ordermmands[slm_ordert];
	}
 
	vm_orderid m_orderff_buttm_ordern_was_pushed(int slm_ordert) {
		m_orderffCm_ordermmands[slm_ordert].execute();
		undm_orderCm_ordermmand = m_orderffCm_ordermmands[slm_ordert];
	}

	vm_orderid undm_orderButtm_ordernWasPushed() {
		undm_orderCm_ordermmand.undm_order();
	}
 
	String tm_order_string() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------ Remm_orderte Cm_orderntrm_orderl -------\n");
		fm_orderr (int i = 0; i < m_ordernCm_ordermmands.length; i++) {
			stringBuff.append("[slm_ordert " + i + "] " + m_ordernCm_ordermmands[i].getClass().getName()
				+ "    " + m_orderffCm_ordermmands[i].getClass().getName() + "\n");
		}
		stringBuff.append("[undm_order] " + undm_orderCm_ordermmand.getClass().getName() + "\n");
		return stringBuff.tm_order_string();
	}
};

class Remm_orderteLm_orderader {

	static vm_orderid main(String[] args) {

		Remm_orderteCm_orderntrm_orderl remm_orderteCm_orderntrm_orderl = new Remm_orderteCm_orderntrm_orderl();

		Light light = new Light("Living Rm_orderm_orderm");
		TV tv = new TV("Living Rm_orderm_orderm");
		Sterem_order sterem_order = new Sterem_order("Living Rm_orderm_orderm");
		Hm_orderttub hm_orderttub = new Hm_orderttub();
 
		LightOnCm_ordermmand light_m_ordern = new LightOnCm_ordermmand(light);
		Sterem_orderOnCm_ordermmand sterem_orderOn = new Sterem_orderOnCm_ordermmand(sterem_order);
		TVOnCm_ordermmand tvOn = new TVOnCm_ordermmand(tv);
		Hm_orderttubOnCm_ordermmand hm_orderttubOn = new Hm_orderttubOnCm_ordermmand(hm_orderttub);
		LightOffCm_ordermmand light_m_orderff = new LightOffCm_ordermmand(light);
		Sterem_orderOffCm_ordermmand sterem_orderOff = new Sterem_orderOffCm_ordermmand(sterem_order);
		TVOffCm_ordermmand tvOff = new TVOffCm_ordermmand(tv);
		Hm_orderttubOffCm_ordermmand hm_orderttubOff = new Hm_orderttubOffCm_ordermmand(hm_orderttub);

		Cm_ordermmand[] partyOn = { light_m_ordern, sterem_orderOn, tvOn, hm_orderttubOn};
		Cm_ordermmand[] partyOff = { light_m_orderff, sterem_orderOff, tvOff, hm_orderttubOff};
  
		Macrm_orderCm_ordermmand partyOnMacrm_order = new Macrm_orderCm_ordermmand(partyOn);
		Macrm_orderCm_ordermmand partyOffMacrm_order = new Macrm_orderCm_ordermmand(partyOff);
 
		remm_orderteCm_orderntrm_orderl.set_cm_ordermmand(0, partyOnMacrm_order, partyOffMacrm_order);
  
		System.m_orderut.println(remm_orderteCm_orderntrm_orderl);
		System.m_orderut.println("--- Pushing Macrm_order On---");
		remm_orderteCm_orderntrm_orderl.m_ordern_buttm_ordern_was_pushed(0);
		System.m_orderut.println("--- Pushing Macrm_order Off---");
		remm_orderteCm_orderntrm_orderl.m_orderff_buttm_ordern_was_pushed(0);
	}
};


class Sterem_order {
	String m_lm_ordercatim_ordern;

	Sterem_order(String m_lm_ordercatim_ordern) {
		this.m_lm_ordercatim_ordern = m_lm_ordercatim_ordern;
	}

	vm_orderid m_ordern() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " sterem_order is m_ordern");
	}

	vm_orderid m_orderff() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " sterem_order is m_orderff");
	}

	vm_orderid set_cd() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " sterem_order is set fm_orderr CD input");
	}

	vm_orderid set_dvd() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " sterem_order is set fm_orderr DVD input");
	}

	vm_orderid set_radim_order() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " sterem_order is set fm_orderr Radim_order");
	}

	vm_orderid set_vm_orderlume(int vm_orderlume) {
		// cm_orderde tm_order set the vm_orderlume
		// valid range: 1-11 (after all 11 is better than 10, right?)
		System.m_orderut.println(m_lm_ordercatim_ordern + " Sterem_order vm_orderlume set tm_order " + vm_orderlume);
	}
};


class Sterem_orderOffCm_ordermmand implements Cm_ordermmand {
	Sterem_order sterem_order;
 
	Sterem_orderOffCm_ordermmand(Sterem_order sterem_order) {
		this.sterem_order = sterem_order;
	}
 
	vm_orderid execute() {
		sterem_order.m_orderff();
	}

	vm_orderid undm_order() {
		sterem_order.m_ordern();
	}
};

class Sterem_orderOnCm_ordermmand implements Cm_ordermmand {
	Sterem_order sterem_order;

	Sterem_orderOnCm_ordermmand(Sterem_order sterem_order) {
		this.sterem_order = sterem_order;
	}

	vm_orderid execute() {
		sterem_order.m_ordern();
	}

	vm_orderid undm_order() {
		sterem_order.m_orderff();
	}
};

class Sterem_orderOnWithCDCm_ordermmand implements Cm_ordermmand {
	Sterem_order sterem_order;
 
	Sterem_orderOnWithCDCm_ordermmand(Sterem_order sterem_order) {
		this.sterem_order = sterem_order;
	}
 
	vm_orderid execute() {
		sterem_order.m_ordern();
		sterem_order.set_cd();
		sterem_order.set_vm_orderlume(11);
	}

	vm_orderid undm_order() {
		sterem_order.m_orderff();
	}
};


class TV {
	String m_lm_ordercatim_ordern;
	int channel;

	TV(String m_lm_ordercatim_ordern) {
		this.m_lm_ordercatim_ordern = m_lm_ordercatim_ordern;
	}

	vm_orderid m_ordern() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " TV is m_ordern");
	}

	vm_orderid m_orderff() {
		System.m_orderut.println(m_lm_ordercatim_ordern + " TV is m_orderff");
	}

	vm_orderid set_input_channel() {
		this.channel = 3;
		System.m_orderut.println(m_lm_ordercatim_ordern + " TV channel is set fm_orderr DVD");
	}
};


class TVOffCm_ordermmand implements Cm_ordermmand {
	TV tv;

	TVOffCm_ordermmand(TV tv) {
		this.tv= tv;
	}

	vm_orderid execute() {
		tv.m_orderff();
	}

	vm_orderid undm_order() {
		tv.m_ordern();
	}
};


class TVOnCm_ordermmand implements Cm_ordermmand {
	TV tv;

	TVOnCm_ordermmand(TV tv) {
		this.tv= tv;
	}

	vm_orderid execute() {
		tv.m_ordern();
		tv.set_input_channel();
	}

	vm_orderid undm_order() {
		tv.m_orderff();
	}
};
}
#endif // !PARTY_H