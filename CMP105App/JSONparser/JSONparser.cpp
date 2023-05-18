#include "JSONparser.h"

JSONparser::JSONparser(const std::string path) {
	std::ifstream is(path);
	json = new std::string(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
	readJSON();
}

JSONparser::~JSONparser() {}

void JSONparser::reset() {
	doc.clear();
	jsonText = "";
	tokens.clear();
	parser = { 0, 0, 0 };
	currentKey = "";
}

void JSONparser::readJSON() {
	char c = json->front();
	size_t position = 0;

	while (position < json->size()) {
		c = json->at(position);
		//json += c;
		switch (c) {
		case '{':
			// check if the token before was a primitive
			if (parser.next_token > 0 && check_if_primitive()) {
				tokens[parser.next_token - 1].end = parser.pos - 1;
				parser.super_token = tokens[parser.next_token - 1].parent;
			}
			// create OBJECT token
			tokens.push_back({ JSON_OBJECT, parser.super_token, parser.pos, 0 });
			// set the super token for next objects
			parser.super_token = parser.next_token;
			parser.next_token++;
			break;
		case '}':
			// check if the token before was a primitive
			if (parser.next_token > 0 && check_if_primitive()) {
				//std::cout << "\nclosed the primitive {}\n";
				tokens[parser.next_token - 1].end = parser.pos - 1;
				parser.super_token = tokens[parser.next_token - 1].parent;
			}
			//std::cout << "\nend: " << tokens[parser.super_token].end << "\n";
			//std::cout << "closing {}: " << parser.super_token << "\n";
			// closes super token
			tokens[parser.super_token].end = parser.pos;
			// set new super token to parent
			parser.super_token = tokens[parser.super_token].parent;
			//std::cout << "super: " << parser.super_token << "\n";
			break;
		case '[':
			tokens.push_back({ JSON_ARRAY, parser.super_token, parser.pos });
			parser.super_token = parser.next_token;
			parser.next_token++;
			break;
		case ']':
			// check if the token before was a primitive
			if (parser.next_token > 0 && check_if_primitive()) {
				//std::cout << "\nclosed the primitive []\n";
				tokens[parser.next_token - 1].end = parser.pos - 1;
				parser.super_token = tokens[parser.next_token - 1].parent;
			}
			for (size_t i = tokens.size() - 1; i >= 0; i--) {
				if (tokens[i].end == 0) {
					// close the array
					tokens[i].end = parser.pos;
					// set new super token to parent
					parser.super_token = tokens[i].parent;
					break;
				}
			}

			break;
		case ':':
			break;
		case '"':
			if (tokens[parser.next_token - 1].type == JSON_STRING && tokens[parser.next_token - 1].end == 0) {
				tokens[parser.next_token - 1].end = parser.pos;
			}
			else {
				tokens.push_back({ JSON_STRING, parser.super_token, parser.pos });
				parser.next_token++;
			}
			break;
		case ',':
			// check if the token before was a primitive
			if (parser.next_token > 0 && check_if_primitive()) {
				tokens[parser.next_token - 1].end = parser.pos - 1;
				parser.super_token = tokens[parser.next_token - 1].parent;
			}
			break;
		case '-':
		case '+':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 't':
		case 'f':
			// if its not an array check if its still an open variable (string/primitive)
			if (tokens[parser.next_token - 1].type != JSON_ARRAY && tokens[parser.next_token - 1].end == 0) {
				break;
			}
			tokens.push_back({ JSON_PRIMITIVE, parser.super_token, parser.pos });
			parser.next_token++;
			break;
		default:
			break;
		}
		parser.pos++;
		position++;
	}

	bool is_key = true;
	bool is_array = false;

	for (int i = 1; i < tokens.size(); i++) {
		parseData(doc, i, is_key, false);
	}
}

void JSONparser::parseData(std::unordered_map<std::string, datatypes>& r, int& i, bool& is_key, bool is_array) {
	int start = tokens[i].start;
	int end = tokens[i].end;
	int len = end - start + 1;

	switch (tokens[i].type) {
	case JSON_OBJECT:
	{
		is_key = true;
		std::string objKey = currentKey;
		int self_token = i;
		if (is_array) {
			datatypes dt;
			dt.type = VAR_OBJECT;
			while (i + 1 < tokens.size() && tokens[i + 1].parent == self_token) {
				dt.size++;
				i++;
				parseData(dt.obj, i, is_key, false);
			}
			dt.size /= 2;
			r[objKey].arr.push_back(dt);
		}
		else {
			r[objKey].type = VAR_OBJECT;
			while (i + 1 < tokens.size() && tokens[i + 1].parent == self_token) {
				r[objKey].size++;
				i++;
				parseData(r[objKey].obj, i, is_key, false);
			}
			r[objKey].size /= 2;
		}
		break;
	}
	case JSON_ARRAY:
	{
		int self_token = i;
		std::string arrKey = currentKey;

		if (is_array) {
			// create a temporary map to store current array
			std::unordered_map<std::string, datatypes> temp;
			while (i + 1 < tokens.size() && tokens[i + 1].parent == self_token) {
				i++;
				parseData(temp, i, is_key, true);
			}

			datatypes vec_arr;
			vec_arr.type = VAR_ARRAY;
			// copy the data from the temp map to the final
			for (int k = 0; k < temp[arrKey].arr.size(); k++) {
				datatypes dt;
				dt.type = temp[arrKey].arr[k].type;
				switch (dt.type) {
				case VAR_INT:
					dt.i = temp[arrKey].arr[k].i;
					break;
				case VAR_DOUBLE:
					dt.d = temp[arrKey].arr[k].d;
					break;
				case VAR_TRUE:
				case VAR_FALSE:
					dt.b = temp[arrKey].arr[k].b;
					break;
				case VAR_STRING:
					dt.str = temp[arrKey].arr[k].str;
					break;
				}
				vec_arr.arr.push_back(dt);
			}
			r[arrKey].arr.push_back(vec_arr);
		}
		else {
			r[arrKey].type = VAR_ARRAY;
			while (i + 1 < tokens.size() && tokens[i + 1].parent == self_token) {
				i++;
				parseData(r, i, is_key, true);
				currentKey = arrKey;
			}
			is_key = true;
		}

		break;
	}
	case JSON_STRING:
	{
		std::string s = json->substr(start + 1, len - 2);
		// it's a key
		if (is_key && !is_array) {
			is_key = false;
			currentKey = s;
			r[currentKey];
		}
		// it's data
		else if (!is_array) {
			is_key = true;
			r[currentKey].str = s;
			r[currentKey].type = VAR_STRING;
		}
		// it's an array value
		else {
			datatypes at;
			at.str = s;
			at.type = VAR_STRING;
			r[currentKey].arr.push_back(at);
		}
		break;
	}
	case JSON_PRIMITIVE:
	{
		std::string data = json->substr(start, len);
		if (is_array) {
			datatypes dt;
			dt.type = parsePrimitive(data);
			switch (dt.type) {
			case VAR_INT:
				dt.i = stoi(data);
				break;
			case VAR_DOUBLE:
				dt.d = stod(data);
				break;
			case VAR_TRUE:
				dt.b = true;
				break;
			case VAR_FALSE:
				dt.b = false;
				break;
			default:
				break;
			}
			r[currentKey].arr.push_back(dt);
			break;
		}
		else {
			r[currentKey].type = parsePrimitive(data);
			switch (r[currentKey].type) {
			case VAR_INT:
				r[currentKey].i = stoi(data);
				break;
			case VAR_DOUBLE:
				r[currentKey].d = stod(data);
				break;
			case VAR_TRUE:
				r[currentKey].b = true;
				break;
			case VAR_FALSE:
				r[currentKey].b = false;
				break;
			default:
				break;
			}
			is_key = true;
			break;
		}
	}
	}
}

bool JSONparser::check_if_primitive() {
	// check if the token before is a primitive and if it's not finished
	return (tokens[parser.next_token - 1].type == JSON_PRIMITIVE && tokens[parser.next_token - 1].end == 0);
}

int JSONparser::parsePrimitive(std::string data) {
	for (int j = 0; j < data.length(); j++) {
		char c = data[j];
		switch (c) {
		case 't':
			return VAR_TRUE;
			break;
		case 'f':
			return VAR_FALSE;
			break;
		case '.':
			return VAR_DOUBLE;
			break;
		}
	}
	return VAR_INT;
}