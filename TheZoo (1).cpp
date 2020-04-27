#include <iostream>
#include <jni.h>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <typeinfo>
using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}


string trim(string trimMe)	//trim spaces from left and right of a string
{
	  // Removes all spaces from the beginning of the string
	    while(trimMe.size() && isspace(trimMe.front()))
	        trimMe.erase(trimMe.begin());
	    // Remove all spaces from the end of the string.
	    while(trimMe.size() && isspace(trimMe.back()))
	       trimMe.pop_back();
	    return trimMe;
}
//Animal clases, following the given hierarchy
struct Animal{
	string Name;	//max chars 15
	int TrackNum;	//exact chars 6
	Animal(string name, int TrackNum): Name(name), TrackNum(TrackNum){}
	virtual ~Animal(){}
};
struct Oviparous: public Animal{
	int NumberOfEggs;
	Oviparous(string name, int TrackNum, int NumberOfEggs): Animal(name, TrackNum), NumberOfEggs(NumberOfEggs){}

};

struct Crocodile: public Oviparous{
	Crocodile(string name, int TrackNum, int NumberOfEggs): Oviparous(name, TrackNum, NumberOfEggs){}
};
struct Goose: public Oviparous{
	Goose(string name, int TrackNum, int NumberOfEggs): Oviparous(name, TrackNum, NumberOfEggs){}
};
struct Pelican: public Oviparous{
	Pelican(string name, int TrackNum, int NumberOfEggs): Oviparous(name, TrackNum, NumberOfEggs){}
};

struct Mammal: public Animal{
	int Nurse;
	Mammal(string name, int TrackNum, int Nurse): Animal(name, TrackNum), Nurse(Nurse){}
};
struct Bat: public Mammal{
	Bat(string name, int TrackNum, int Nurse): Mammal(name, TrackNum, Nurse){}
};
struct Whale: public Mammal{
	Whale(string name, int TrackNum, int Nurse): Mammal(name, TrackNum, Nurse){}
};
struct SeaLion: public Mammal{
	SeaLion(string name, int TrackNum, int Nurse): Mammal(name, TrackNum, Nurse){}
};

//global zoo vector, uses unique_ptr to allow polymorph
vector<unique_ptr<Animal>> Zoo;

//Animal functions
void AddAnimal()
{
	string track;
	string name;
	string type;
	string sub;
	string eggs;
	string nurse;
	char save;

	cout << "Enter Track#:" << endl;
	cin >> track;
	cout << "Enter Name:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Enter Type:" << endl;
	cin >> type;
	cout << "Enter Sub-type:" << endl;
	cin >> sub;
	cout << "Enter number of Eggs:" << endl;
	cin >> eggs;
	cout << "Enter if Nursing (1 for yes, 0 for no):" << endl;
	cin >> nurse;

	cout << track << " " << name << " " << type << " " << sub << " " << eggs << " " << nurse << endl;
	cout << "Would you like to save this data? (Y for yes)" << endl;
	cin >> save;
	bool good = true;
	if(save == 'Y'){	//check all data dilemmas

		for (int i = 0; i < track.length(); i++){
		      if (!isdigit(track[i]) || track.length() > 6){
		    	  cout << track << " is not up to a 6 digit number" << endl;
		    	  good = false;
		    	  break;
		      }
		}
		for (int i = 0; i < eggs.length(); i++){
		      if (!isdigit(eggs[i])){
		    	  cout << eggs << " is not a correctly input number" << endl;
		    	  good = false;
		    	  break;
		      }
		}
		for (int i = 0; i < nurse.length(); i++){
		      if (!isdigit(nurse[i])){
		    	  cout << nurse << " is not a correctly input number" << endl;
		    	  good = false;
		    	  break;
		      }
		}
		int trackI = stoi(track);
		int eggsI = stoi(eggs);
		int nurseI = stoi(nurse);

		if(type != "Mammal" && type != "Oviparous"){
			cout << type << " is not Mammal or Oviparous" << endl;
			good = false;
		}
		if(type == "Mammal"){
			if(sub != "Bat" && sub != "Whale" && sub != "SeaLion"){
				cout << sub << " is not a Bat, Whale, or SeaLion" << endl;
				good = false;
			}
		}else{
			if(sub != "Crocodile" && sub != "Goose" && sub != "Pelican"){
				cout << sub << " is not a Crocodile, Goose, or Pelican" << endl;
				good = false;
			}
		}
		if(eggsI > 0 && nurseI > 0){
			cout << "We don't do platypus..." << endl;
			good = false;
		}
		if(good){
			name = name.substr(0, 15);

			if(type == "Mammal"){
				if(sub == "Bat"){
					Zoo.push_back(unique_ptr<Animal>(new Bat(name, trackI, nurseI)));
				}else if(sub == "Whale"){
					Zoo.push_back(unique_ptr<Animal>(new Whale(name, trackI, nurseI)));
				}else{
					Zoo.push_back(unique_ptr<Animal>(new SeaLion(name, trackI, nurseI)));
				}
			}else{
				if(sub == "Crocodile"){
					Zoo.push_back(unique_ptr<Animal>(new Crocodile(name, trackI, eggsI)));
				}else if(sub == "Goose"){
					Zoo.push_back(unique_ptr<Animal>(new Goose(name, trackI, eggsI)));
				}else{
					Zoo.push_back(unique_ptr<Animal>(new Pelican(name, trackI, eggsI)));
				}
			}
			cout << "Animal Saved" << endl;
		}else{
			cout << "You entered some data wrong, try again." << endl;
		}
		cout << "Exiting to  menu..." << endl;
		return;
	}


}


void RemoveAnimal()
{
	string trackS;
	cout << "Enter the Tracking Number of the Animal you want to remove." << endl;
	cin >> trackS;
	for (int i = 0; i < trackS.length(); i++){
	      if (!isdigit(trackS[i]) || trackS.length() > 6){
	    	  cout << trackS << " is not a vaild input" << endl;
	    	  return;
	      }
	}
	int trackI = stoi(trackS);
	for(int i = 0; i < Zoo.size(); i++){
		if(trackI == static_cast<Animal*>(Zoo[i].get())->TrackNum){
			Zoo.erase(Zoo.begin() + i);
			cout << "Data Deleted" << endl;
			return;
		}
	}
	cout << "No such data exists.";


}

void LoadDataFromFile()
{
	ifstream in ("zoodata.txt");
	string line;

	while(getline(in, line)){
		if(line.size()>0){
			int trackNum;
			string name;
			string type;
			string subType;
			int eggs;
			int nurse;

			trackNum = stoi(line.substr(0, 7));
			name = trim(line.substr(8, 15));
			type = trim(line.substr(25, 15));
			subType = trim(line.substr(42, 15));
			eggs = stoi(line.substr(59, 1));
			nurse = stoi(line.substr(61, 1));

			if(type.find("Oviparous") != string::npos){

				if(subType.find("Crocodile") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new Crocodile(name, trackNum, eggs)));
				}
				if(subType.find("Goose") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new Goose(name, trackNum, eggs)));
				}
				if(subType.find("Pelican") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new Pelican(name, trackNum, eggs)));
				}
			}
			if(type.find("Mammal") != string::npos){
				if(subType.find("Bat") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new Bat(name, trackNum, nurse)));
				}
				if(subType.find("Whale") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new Whale(name, trackNum, nurse)));
				}
				if(subType.find("SeaLion") != string::npos){
					Zoo.push_back(unique_ptr<Animal>(new SeaLion(name, trackNum, nurse)));
				}
			}
		}
	}
	cout << "Data Loaded" << endl;
}
//functions to test for animal object type
string getType(int i){
	if(dynamic_cast<Mammal*>(Zoo[i].get()) != 0){
		return "Mammal";
	}else{
		return "Oviparous";
	}
}
string getSubType(int i){
	if(getType(i) == "Mammal"){
		if(dynamic_cast<Bat*>(Zoo[i].get()) != 0){
			return "Bat";
		}
		if(dynamic_cast<Whale*>(Zoo[i].get()) != 0){
			return "Whale";
		}
		if(dynamic_cast<SeaLion*>(Zoo[i].get()) != 0){
			return "SeaLion";
		}
	}else{
		if(dynamic_cast<Crocodile*>(Zoo[i].get()) != 0){
			return "Crocodile";
		}
		if(dynamic_cast<Goose*>(Zoo[i].get()) != 0){
			return "Goose";
		}
		if(dynamic_cast<Pelican*>(Zoo[i].get()) != 0){
			return "Pelican";
		}
	}
	return "Unknown";
}
//nearly carbon copy of those in ZooFileWriter.java
string padLeft(string str, int leng, string stringpadVal) {
        for (int i = str.length(); i <= leng; i++)
            str = stringpadVal + str;
        return str;
    }
string padRight(string str, int leng, string stringpadVal) {
        for (int i = str.length(); i <= leng; i++)
            str = str + stringpadVal;
        return str;
    }
//handles the padding
string dress(string track, string name, string type, string sub, string eggs, string nurse){
	string out = "";
	out += padLeft(track, 6, "0");
	out += " ";
	out += padRight(name, 15, " ");
	out += " ";
	out += padRight(type, 15, " ");
	out += " ";
	out += padRight(sub, 15, " ");
	out += " ";
	out += eggs;
	out += " ";
	out += nurse;

	return out;
}

void SaveDataToFile()
{
	ofstream out("zoodata.txt");
	for(unsigned int i = 0; i < Zoo.size(); i++){
		if(getType(i) == "Oviparous"){
			out << dress(to_string(static_cast<Animal*>(Zoo[i].get())->TrackNum),
					static_cast<Animal*>(Zoo[i].get())->Name,
					"Oviparous",
					getSubType(i),
					to_string(static_cast<Oviparous*>(Zoo[i].get())->NumberOfEggs),
					"0");
		}else if(getType(i) == "Mammal"){
			out << dress(to_string(static_cast<Animal*>(Zoo[i].get())->TrackNum),
					static_cast<Animal*>(Zoo[i].get())->Name,
					"Mammal",
					getSubType(i),
					"0",
					to_string(static_cast<Mammal*>(Zoo[i].get())->Nurse));

		}
		if(i < Zoo.size()-1){
			out << endl;
		}
	}
	cout << "Data Saved" << endl;
}

void DisplayMenu()
{
	cout << "Enter an option:" << endl;
	cout << "1: Load Animal Data" << endl;
	cout << "2: Generate Data" << endl;
	cout << "3: Display Animal Data" << endl;
	cout << "4: Add Record" << endl;
	cout << "5: Delete Record" << endl;
	cout << "6: Save Animal Data" << endl;
	cout << "7: Quit" << endl;
}

void DisplayAnimalData(){
	cout << Zoo.size() << " Animals Found!" << endl;
	cout << dress(" Track#", "Name", "Type", "Sub-Type", "Eggs", "Nurse") << endl;
	for(unsigned int i = 0; i < Zoo.size(); i++){
		if(getType(i) == "Oviparous"){
		cout << dress(to_string(static_cast<Animal*>(Zoo[i].get())->TrackNum),
			static_cast<Animal*>(Zoo[i].get())->Name,
			"Oviparous",
			getSubType(i),
			to_string(static_cast<Oviparous*>(Zoo[0].get())->NumberOfEggs),
			"0");
		}else if(getType(i) == "Mammal"){
			cout << dress(to_string(static_cast<Animal*>(Zoo[i].get())->TrackNum),
				static_cast<Animal*>(Zoo[i].get())->Name,
				"Mammal",
				getSubType(i),
				"0",
				to_string(static_cast<Mammal*>(Zoo[0].get())->Nurse));

		}
		cout << endl;
	}
}

int main()
{
	//LoadDataFromFile();
	int option = 0;
	bool cont = false;
	do{
		cont = true;

		DisplayMenu();
		cin >> option;


		switch(option){
		case 1:
			LoadDataFromFile();
			break;
		case 2:
			GenerateData();
			break;
		case 3:
			DisplayAnimalData();
			break;
		case 4:
			AddAnimal();
			break;
		case 5:
			RemoveAnimal();
			break;
		case 6:
			SaveDataToFile();
			break;
		case 7:
		default:
			cont = false;
			break;
		}

	}while(cont);

	return 1;
}
