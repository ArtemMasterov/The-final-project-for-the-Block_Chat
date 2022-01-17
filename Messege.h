#pragma once
#include "User.h"
using namespace std;

class Messege
{
private:
const string _from;
const string _to;
const string _text;

public:
	Messege(const string& from, const string& to, const string& text) : _from(from), _to(to), _text(text) {}

		const string& getFrom() const { return _from; }
		const string& getTo() const { return _to; }
		const string& getText() const {return _text; }
};
