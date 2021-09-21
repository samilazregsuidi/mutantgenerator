#include <string>

class mTypeList {
public:
	mTypeList(const std::string& name);
	void printMTypes(void);
	mTypeList* addMType(const std::string& name);
	int getMTypeValue(const std::string& name) const;
	std::string getMTypeName(int value) const;
	std::string getName(void) const;

private:
	int value;					// Automatically incremented integer value
	std::string name;					// Name given by user
	mTypeList* next;	// Points to next node; the last node in a list has this pointer set to NULL.
	mTypeList* prev;	// Points to previous node; the first node in a list has this pointer pointing to the last node!
};