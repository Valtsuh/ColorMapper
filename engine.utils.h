typedef int DINT;
typedef signed int SINT;
typedef long int LINT;
typedef long long int SLINT;
typedef long double LBLE;


#define ENGINE_DATABASE_LIST_LENGTH_MAX 128
#define ENGINE_DATABASE_INDEX_BLOCK_SIZE 8
#define ENGINE_TEXT_MAX_LENGTH 64
#define ENGINE_DRAW	101
#include <time.h>
#include <chrono>
#include <thread>
#include <fstream>

struct BINT {
	BINT(DINT value = 0) {
		this->value = value;
	};
	~BINT() {
		this->value = 0;
	};
	DINT value;

	operator DINT() const {
		return this->value;
	}

	DINT operator++(int amount) {
		this->value = this->value + 1;
		return this->value;
	}

	DINT operator--(int amount) {
		if (this->value > 0) this->value = this->value - 1;
		return this->value;
	}
};

struct DUAL {
	SINT i;
	double d;

	operator SINT() const {
		return this->i;
	}
};
struct COUNTER {
	COUNTER(DINT total = 0) {
		this->value = 0;
		this->current = total;
		this->total = total;
	};
	~COUNTER() {
		this->value = 0;
		this->current = 0;
		this->total = 0;
	};
	SINT value, current, total;

	operator SINT() const {
		return this->current;
	}
	void operator =(SINT value) {
		this->current = value;
	}

	void _add(DINT value = 0) {
		this->current += value;
		this->total += value;
	}

	DINT _difference(COUNTER counter) {
		return this->current - counter.current;
	}

	void _reset() {
		this->current = 0;
		this->total = 0;
		this->value = 0;
	}

	DINT _full() {
		return (this->current >= this->total) ? (1) : (0);
	}
};
struct TIME {
	TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
		this->success = 0;
		this->precision = 0;
		this->count = 0;
		this->system = {};
		this->difference = 0;
		this->elapsed = 0;
		this->lh = 0;
		this->lm = 0;
		this->ls = 0;
		this->lms = 0;
	};
	~TIME() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
		this->count = 0;
		this->elapsed = 0;
		this->difference = 0;
	};
	DINT year, month, day, hour, minute, second, success, precision, elapsed, difference;
	DINT millisecond, microsecond, nanosecond;
	LINT count;
	SYSTEMTIME system;
	DINT lh, lm, ls, lms;

	void _clock(DINT type = 1) {
		this->_reset();
		switch (type) {
		default:
			GetLocalTime(&this->system);
			this->month = this->system.wMonth;
			this->day = this->system.wDay;
			this->hour = this->system.wHour;
			this->minute = this->system.wMinute;
			this->second = this->system.wSecond;
			this->millisecond = this->system.wMilliseconds;
			this->microsecond = 0;
			this->nanosecond = 0;
			break;
		case 1:
			//std::chrono::time_point<std::chrono::system_clock> tp = std::chrono::system_clock::now();
			std::chrono::steady_clock::time_point tp = std::chrono::high_resolution_clock::now();
			auto duration = tp.time_since_epoch();
			typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<2>>::type> Days;

			Days days = std::chrono::duration_cast<Days>(duration);
			this->day = (DINT)days.count();
			duration -= days;

			auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
			this->hour = (DINT)hours.count(); // +13;
			duration -= hours;

			auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
			duration -= minutes;
			this->minute = (DINT)minutes.count();

			auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
			duration -= seconds;
			this->second = (DINT)seconds.count();

			auto mss = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
			duration -= mss;
			this->millisecond = (DINT)mss.count();

			auto uss = std::chrono::duration_cast<std::chrono::microseconds>(duration);
			duration -= uss;
			this->microsecond = (DINT)uss.count();

			auto nss = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
			this->nanosecond = (DINT)nss.count();
			break;
		}
		DINT view = 0;
		if (view) {
			std::cout << "\nYear: " << this->year;
			std::cout << "\nMonth: " << this->month;
			std::cout << "\nDay: " << this->day;
			std::cout << "\nHour: " << this->hour;
			std::cout << "\nMinute: " << this->minute;
			std::cout << "\nSecond: " << this->second;
			std::cout << "\nMs: " << this->millisecond;
			std::cout << "\nMcrs: " << this->microsecond;
			std::cout << "\nNs: " << this->nanosecond;
		}
	}

	DINT _duration(TIME time, DINT ms = 0) {
		this->count = 0;
		this->_clock(0);
		this->hour = (this->hour > time.hour) ? ((this->hour == 0) ? (11) : (0)) : (this->hour);
		//this->count += (LINT)this->year * 12 * 30 * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->month * 30 * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->day * 24 * 60 * 60 * 1000;
		//this->count += (LINT)this->hour * 60 * 60 * 1000;
		this->count += (LINT)this->minute * 60 * 1000;
		this->count += (LINT)this->second * 1000;
		this->count += (LINT)this->millisecond;
		time.hour = (time.hour > this->hour) ? ((time.hour == 0) ? (11) : (0)) : (time.hour);
		//time.count += (LINT)time.year * 12 * 30 * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.month * 30 * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.day * 24 * 60 * 60 * 1000;
		//time.count += (LINT)time.hour * 60 * 60 * 1000;
		time.count += (LINT)time.minute * 60 * 1000;
		time.count += (LINT)time.second * 1000;
		time.count += (LINT)time.millisecond;
		switch (ms) {
		default:
			this->elapsed = (DINT)((this->count - time.count) / 1000);
			break;
		case 1:
			this->elapsed = (DINT)(this->count - time.count);
			break;
		}
		return this->elapsed;
	}
	void _increment(TIME time) {
		this->_clock(0);
		this->count += (LINT)this->hour * 60 * 60 * 1000;
		this->count += (LINT)this->minute * 60 * 1000;
		this->count += (LINT)this->second * 1000;
		this->count += (LINT)this->millisecond;
		time.count += (LINT)time.hour * 60 * 60 * 1000;
		time.count += (LINT)time.minute * 60 * 1000;
		time.count += (LINT)time.second * 1000;
		time.count += (LINT)time.millisecond;
		this->lms += (this->count > time.count) ? ((DINT)(this->count - time.count)) : ((DINT)(time.count - this->count));
		for (; this->lms > 999; this->lms -= 1000) {
			this->ls += 1;
		}
		for (; this->ls > 59; this->ls -= 60) {
			this->lm += 1;
		}
		for (; this->lm > 59; this->lm -= 60) {
			this->lh += 1;
		}
		this->count = 0;

	}
	void _reset() {
		this->count = 0;
		this->difference = 0;
		this->year = 0;
		this->month = 0;
		this->day = 0;
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
		this->millisecond = 0;
		this->microsecond = 0;
		this->nanosecond = 0;
	}

	DINT _since(DINT ms = 0) {
		DINT count = 0;
		//std::cout << "\n>" << this->lh << ": " << this->lm << ":" << this->ls;
		count += this->lh * 60 * 60;// *(ms) ? (1000) : (1);
		count += this->lm * 60;// *(ms) ? (1000) : (1);
		count += this->ls;// *(ms) ? (1000) : (1);
		//std::cout << " - " << count;
		return count;
	}
};

struct DICE {
	DICE() {
		this->seed.i = 0;
		this->seed.d = 0.0;
		this->value.i = 0;
		this->seed.d = 0.0;

	};

	DUAL seed, value;
	TIME time;
	operator DICE() const {
		return *this;
	}
	SINT _roll(SINT min, SINT max) {
		this->time._clock();
		this->seed.i = (this->time.microsecond) % (max + 1 - min); // 0 - 9
		this->value.i = this->seed.i + min;
		this->value.i = (this->value.i > max) ? (max) : (this->value.i);
		//std::cout << "\nSeed: " << this->seed.i << ", Value: " << this->value.i << " (" << min << ", " << max << ")";
		return this->value.i;
	}

	double _droll(double min, double max, double accuracy = 0.01) {
		this->time._clock();
		if (min > max) {
			double tmin = min;
			min = max;
			max = tmin;
		}
		double addition = 0.0;
		DINT cmin = 0, cmax = 0;
		DINT hcount = 0;

		double nmin = min;
		double nmax = max;
		do {
			nmin += 1.0;
			addition += 1.0;
		} while (nmin < 0.0);

		do {
			nmin *= 10.0;
			cmax++;
		} while (min / nmin > accuracy);
		SINT dmin = (SINT)nmin;
		nmax += addition;
		do {
			nmax *= 10.0;
			cmin++;
		} while (max / nmax > accuracy);
		SINT dmax = (SINT)nmax;
		DINT value = 1;
		hcount = (cmin > cmax) ? (cmin) : (cmax);
		for (DINT c = 1; c <= hcount + 2; c++) {
			value *= value * c + this->_roll(10, 20);
		}
		this->seed.i = (this->time.microsecond * value) % (dmax + 1 - dmin);
		this->value.i = this->seed.i + dmin;
		this->value.d = (double)this->value.i;
		for (DINT c = 0; c < hcount; c++) {
			this->value.d /= 10.0;
		}
		this->value.d -= addition;
		if (this->value.d < min) this->value.d = min;
		//std::cout << "\nDouble roll: " << this->value.d << " (" << min << ", " << max << ")";
		return this->value.d;

	}

};
struct RANDOM {
	RANDOM() {
		this->min = 0;
		this->max = 1;
		this->value = 0;
	};
	~RANDOM() {
		this->min = 0;
		this->max = 1;
		this->value = 0;
	};
	DINT min, max, value;


	DINT _roll(SINT min = -1, SINT max = -1) {
		if (min < 0 && max >= 0) {
			if (this->min == 0) max++;
			this->value = rand() % max + this->min;
		}
		if (min >= 0 && max < 0) {
			if (min == 0) this->max++;
			this->value = rand() % this->max + min;
			if (min == 0) this->max--;
		}
		if (min < 0 && max < 0) {
			if (this->min == 0) this->max++;
			this->value = rand() % this->max + this->min;
			if (this->min == 0) this->max--;
		}
		if (min >= 0 && max >= 0) {
			if (min == 0) max++;
			this->value = rand() % max + min;
		}
		return this->value;
	}

	double _droll(double min = -1.0, double max = 1.0) {
		double value = 0.0;
		value = min + (double)(rand() % (SINT)max) + max / 2;
		std::cout << "\nRoll: " << value;
		return value;
	}

};

struct DIMENSION {
	DIMENSION(DINT x = 0, DINT y = 0) {
		this->x = x;
		this->y = y;
		this->w = 0;
		this->h = 0;
		this->size = 0;
		this->direction = 0;
	}
	~DIMENSION() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->size = 0;
		this->direction = 0;
	};
	DINT x, y, w, h, size, direction;

	DINT _within(DINT x, DINT y) {
		return (x >= this->x && x <= this->w + this->x && y >= this->y && y <= this->h + this->y);
	}
	void _set(DIMENSION dimension) {
		this->x = dimension.x;
		this->y = dimension.y;
		this->w = dimension.w;
		this->h = dimension.h;
		this->size = dimension.size;
	}
};
struct SPOT {
	SPOT(double x = 0.0, double y = 0.0, double z = 0.0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	~SPOT() {};
	double x, y, z;
};
struct STRING {
	STRING() {
		this->length = 0;
		this->wtext[this->length] = L'\0';
		this->utext[this->length] = (unsigned char)'\0';
		this->text[this->length] = '\0';
	};
	~STRING() {
		this->length = 0;
		*this->wtext = {};
		*this->text = {};
		*this->utext = {};
	};
	DINT length;
	wchar_t wtext[ENGINE_TEXT_MAX_LENGTH];
	char text[ENGINE_TEXT_MAX_LENGTH];
	unsigned char utext[ENGINE_TEXT_MAX_LENGTH];
	DICE dice;

	void _generate(DINT length = 5) {
		if (length > ENGINE_TEXT_MAX_LENGTH - 1) length = ENGINE_TEXT_MAX_LENGTH - 1;
		this->_clear();
		for (; length > this->length;) {
			switch (this->dice._roll(0, 8)) {
			default:
				this->_append("A");
				break;
			case 0:
				this->_append("No");
				break;
			case 1:
				this->_append("Ka");
				break;
			case 2:
				this->_append("o");
				break;
			case 3:
				this->_append("V");
				break;
			case 4:
				this->_append("de");
				break;
			case 5:
				this->_append("r");
				break;
			case 6:
				this->_append("qu");
				break;
			case 7:
				this->_append("s");
				break;
			}
		}
		this->text[length] = '\0';
	}

	void _append(const char text[]) {
		for (DINT i = 0; text[i] != '\0'; i++) {
			this->text[this->length] = text[i];
			this->wtext[this->length] = (wchar_t)text[i];
			this->length++;
		}
		this->text[this->length] = '\0';
		this->wtext[this->length] = L'\0';
	}

	void _space(const char text[]) {
		if (this->length != 0) {
			this->text[this->length] = ' ';
			this->wtext[this->length] = L' ';
			this->length++;
		}
		this->_append(text);
	}

	void _add(char character) {
		this->text[this->length] = character;
		this->length++;
	}

	void _erase() {
		this->~STRING();
		*this = {};
	}

	void _clear() {
		if (this->length > 0) {
			for (; this->length > 0; this->length--) {
				this->text[this->length - 1] = '\0';
				this->utext[this->length - 1] = (unsigned char)'\0';
				this->wtext[this->length - 1] = L'\0';
			}
		}
	}

	void _reverse() {
		STRING temp = {};
		temp._clear();
		for (temp.length = 0; temp.length < this->length; temp.length++) {
			temp.wtext[temp.length] = this->wtext[this->length - temp.length - 1];
			temp.text[temp.length] = this->text[this->length - temp.length - 1];
			temp.utext[temp.length] = this->utext[this->length - temp.length - 1];
		}
		*this = temp;


	}

	void _write(const char text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = text[this->length];
			this->wtext[this->length] = (wchar_t)text[this->length];
			this->utext[this->length] = (unsigned char)text[this->length];
		}
		this->text[this->length] = '\0';
		this->wtext[this->length] = L'\0';
		this->utext[this->length] = (unsigned char)'\0';
	}

	void _uwrite(unsigned char text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = (wchar_t)text[this->length];
			this->utext[this->length] = text[this->length];
		}
		this->text[this->length] = '\0';
	}

	void _wwrite(const wchar_t text[]) {
		this->_clear();
		for (this->length = 0; text[this->length] != '\0'; this->length++) {
			this->text[this->length] = (char)text[this->length];
			this->wtext[this->length] = text[this->length];
			this->utext[this->length] = (unsigned char)text[this->length];
		}
		this->text[this->length] = '\0';
	}
};

struct FIGURE {
	FIGURE() {
		this->current = 0.0;
		this->total = 0.0;
		this->value = 0.0;
	};
	~FIGURE() {};
	double current, total, value;

	void _add(double amount) {
		this->current += amount;
		this->total += amount;
	}

};
template <typename T>
struct HOLDER {
	HOLDER(std::initializer_list<T> ts) {
		this->ts = ts;
	};
	HOLDER() {};
	std::initializer_list<T> ts;
	T operator[](DINT position) {
		return *(this->ts.begin() + position);
	}
	DINT _size() {
		return this->ts.size();
	}
};
template <typename LIST_ITEM>
struct LIST {
	LIST() {
		this->length = 0;
		this->total = 0;
		this->last = -1;
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) this->exist[i] = 0;
	};
	~LIST() {
		this->last = -1;
		this->length = 0;
		this->total = 0;
	};

	DINT length, total;
	SINT last;
	LIST_ITEM item[ENGINE_DATABASE_LIST_LENGTH_MAX]; // approx. max array length
	DINT exist[ENGINE_DATABASE_LIST_LENGTH_MAX];

	DINT _exist(DINT position) {
		return this->exist[position];
	}

	DINT _amount() {
		DINT a = 0, b = 0;
		do {
			if (this->exist[a] == 1) a++;
			b++;
		} while (b < ENGINE_DATABASE_LIST_LENGTH_MAX);
		return a;
	}

	void _add(LIST_ITEM item) {
		DINT pos = (this->last != -1) ? (this->last) : (this->length);
		this->item[pos] = item;
		this->exist[pos] = 1;
		this->length++;
		this->total++;
	}

	void _open(LIST_ITEM item) {
		for (DINT i = 0; i < ENGINE_DATABASE_LIST_LENGTH_MAX; i++) {
			if (this->exist[i] == 0) {
				this->item[i] = item;
				this->item[i] = 1;
				break;
			}
		}
	}

	void _total() {
		DINT i = 0;
		for (DINT e = 0; e < ENGINE_DATABASE_LIST_LENGTH_MAX; e++) {
			if (this->exist[e]) i++;
		}
		this->total = i;
	}

	void _remove(DINT position = 0) {
		LIST_ITEM item = {};
		this->item[position] = item;
		this->existance[position] = 0;
		this->length--;
		this->last = position;
	}

	void _specific(LIST_ITEM item, DINT position) {
		this->item[position] = item;
		this->exist[position] = 1;
		this->length++;
	}

	LIST_ITEM _get(DINT position = 0) {
		return this->item[position];
	}

	void _clear() {
		this->~LIST();
		*this = {};
	}
};

template <typename ITEM>
struct INDEX {
	INDEX(DINT block = ENGINE_DATABASE_INDEX_BLOCK_SIZE) {
		this->length = 0;
		this->total = 0;
		this->size = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->current = 0;
		this->block = block;
		this->identifier = 0;
		this->last = -1;
		//std::cout << "\nIndex constructor called. (" << this->identifier << ")";
	};
	~INDEX() {
		this->length = 0;
		this->total = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->size = 0;
		this->block = 0;
		this->last = -1;
	};
	BINT length, size, total, current, block, identifier;
	SINT last;
	ITEM* item;
	BINT* exist;
	DICE dice;

	void _add(ITEM item) {
		//INDEX <ITEM> *current = this;
		if (this->size == 0) {
			this->identifier = this->dice._roll(0, 999);
		}
		if (this->size <= this->length) {
			//if (this->size == 0) std::cout << "\nCreating index."; else std::cout << "\nResizing index.";
			DINT size = this->size + this->block;
			INDEX <ITEM>* n = new INDEX <ITEM>;
			n->item = new ITEM[size];
			n->exist = new BINT[size];
			n->size = size;
			n->total = this->total;
			n->block = this->block;
			DINT i = 0;

			for (DINT j = 0; n->length < this->size && j < this->size; j++) {
				if (this->exist[j] == 1) {

					n->item[n->length] = this->item[j];

					n->exist[n->length] = 1;
					this->exist[j] = 0;

					n->length = n->length + 1;
				}
			}

			n->item[n->length] = item;
			n->exist[n->length] = 1;
			n->length = n->length + 1;
			n->total = n->total + 1;
			delete[] this->exist;
			delete[] this->item;
			*this = *n;
			n->_clear();
			delete[] n->item;
			delete[] n->exist;
			delete n;
		}
		else {
			for (DINT p = 0; p < this->size; p++) {
				if (this->exist[p] == 0) {
					this->item[p] = item;
					this->exist[p] = 1;
					this->length = this->length + 1;
					this->total = this->total + 1;
					this->last = p;
					break;
				}
			}
		}
		/*
		INDEX <ITEM>* n = new INDEX <ITEM>;
		n->item = new ITEM[this->length + 1];
		n->exist = new BINT[this->length + 1];
		DINT i = 0;

		for (DINT j = 0; n->length < this->length && j < this->length; j++) {
			if (this->exist[j]) {
				n->item[n->length] = this->item[j];
				this->item[j] = {};
				n->exist[n->length] = 1;
				this->exist[j] = 0;
				n->length = n->length + 1;
			}
		}
		n->item[n->length] = item;
		n->exist[n->length] = 1;
		n->length = n->length + 1;

		delete[] this->item;
		delete[] this->exist;
		this->_clear();
		*this = *n;
		n->_clear();
		delete[] n->exist;
		delete[] n->item;
		delete (n);
		*/
		/*
		if (current->length > 0) {
			do {
				if (current->exist[i] == 1) {

					n->item[n->length] = current->item[i];
					current->item[i] = {};
					this->item[i] = {};

					n->exist[n->length] = 1;
					current->exist[i] = 0;
					this->exist[i] = 0;

					n->length++;
				}
				i++;
			} while (n->length < current->length && i < current->length);
		}
		*/
		//current->_clear();
	}

	void _remove(DINT position) {
		if (position >= 0 && position < this->size) {
			this->exist[position] = 0;
			this->length = this->length - 1;
		}
		/*
		INDEX <ITEM>* current = this;
		INDEX <ITEM>* n = new INDEX <ITEM>;
		n->item = new ITEM[current->length - 1];
		n->exist = new DINT[current->length - 1];
		for (DINT j = 0; n->length < this->length && j < this->length; j++) {
			if (this->exist[j]) {
				n->item[n->length] = this->item[j];
				this->item[j] = {};
				n->exist[n->length] = 1;
				this->exist[j] = 0;
				n->length++;
			}
		}
		*/
		/*
		DINT i = 0;
		do {
			if (current->exist[i] == 1) {
				n->item[n->length] = current->item[i];
				current->item[i] = {};
				this->item[i] = {};

				n->exist[n->length] = 1;
				current->exist[i] = 0;
				this->exist[i] = 0;
				n->length++;
			}
			i++;
		} while (n->length < current->length && i < current->length);
		*/
		/*
		delete[] this->item;
		delete[] this->exist;
		this->_clear();
		current->_clear();
		*this = *n;
		n->_clear();
		delete (n);
		*/
	}

	ITEM _get(DINT position) {
		if (position < this->length) {
			if (this->exist[position] == 1) return this->item[position];
		}
		ITEM item = {};
		return item;
	}

	void _clear() {
		this->length = 0;
		this->current = 0;
		this->total = 0;
		this->item = { 0 };
		this->exist = { 0 };
		*this = {};
	}

	void _reverse() {
		INDEX <ITEM>* list = new INDEX<ITEM>;
		list->item = new ITEM[this->size];
		list->exist = new BINT[this->size];
		for (DINT r = this->size; r > 0; r--) {
			if (this->exist[r - 1] == 1) {
				list->_add(this->item[r - 1]);
			}
		}
		*this = *list;
		list->_clear();

		delete[] list->item;
		delete[] list->exist;
		delete list;
	}

	SINT _first(DINT offset = 0) {
		if (offset >= this->size) offset = this->size - 1;
		for (DINT i = offset; i < this->size; i++) {
			if (this->exist[i] == 1) return i;
		}
		return -1;
	}

	void _swap(DINT a, DINT b) {
		if (a < this->size && b < this->size && a != b) {
			ITEM one = this->item[a];
			DINT c = this->exist[a];
			this->item[a] = this->item[b];
			this->exist[a] = this->exist[b];
			this->item[b] = one;
			this->exist[b] = c;

		}
	}

	void _pop(SINT side = 1) {
		SINT popped = -1;

		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i] == 1) {
				popped = i;
				if (side == -1) break;
			}
		}
		if (popped >= 0) {
			this->exist[popped] = 0;
			this->item[popped] = { 0 };
		}
	}

	void _pend(ITEM item, SINT side = 1) {
		if (side == -1) {
		}
		else {

		}
	}


	void _close() {
		if (this->length > 0) {
			delete[] this->item;
			delete[] this->exist;
			delete this;
		}
	}
};

template <typename ITEM>
struct CHART {
	CHART(DINT block = 8) {
		//std::cout << "\nConstructing chart.";
		this->block = block;
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->filled = 0;
		//this->item = new ITEM[this->block];
		//this->exist = new BINT[this->block];
		this->dummy = {};
	}
	CHART(std::initializer_list<ITEM> l) {
		this->size = 0;
		this->length = 0;
		this->last = 0;
		this->item = { 0 };
		this->exist = { 0 };
		this->filled = 0;
		//this->item = new ITEM[this->block];
		//this->exist = new BINT[this->block];
		this->dummy = {};
		HOLDER<ITEM> items = l;
		this->block = items._size();
		for (DINT i = 0; i < items._size(); i++) {
			ITEM item = items[i];
			*this << item;
		}

	}
	~CHART() {
		this->size = 0;
		this->block = 0;
		this->filled = 0;
		this->last = 0;
		this->length = 0;
		this->total = 0;
	}
	DINT size, block, filled, length;
	SINT last;
	BINT total;
	ITEM* item;
	ITEM dummy;
	BINT* exist;
	STRING name;

	void _resize(DINT size = 0) {
		DINT total = this->size;
		if (size > 0) {
			this->size = size;
		}
		else {
			this->size = this->size + this->block;
		}
		DINT l = 0;
		if (total > 0) {
			ITEM* items = new ITEM[total];
			BINT* exists = new BINT[total];
			for (DINT k = 0; k < total; k++) {
				if (this->exist[k]) {
					items[l] = this->item[k];
					exists[l] = 1;
					l++;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
			DINT j = 0;
			for (this->length = 0; this->length < l && j < this->size; this->length++) {
				if (exists[this->length]) {
					this->item[j] = items[this->length];
					this->exist[j] = 1;
					j++;
				}
			}
			delete[] items;
			delete[] exists;
		}
		else {
			this->item = new ITEM[this->size];
			this->exist = new BINT[this->size];
		}
	};

	DINT _existance() {
		if (this->size > 0) {
			ITEM* item = new ITEM[this->length];
			BINT* exist = new BINT[this->length];
			DINT j = 0;
			for (DINT i = 0; i < this->size; i++) {
				if (this->exist[i]) {
					item[j] = this->item[i];
					exist[j] = 1;
				}
			}
			delete[] this->item;
			delete[] this->exist;
			this->item = new ITEM[j];
			this->exist = new BINT[j];
			for (this->length = 0; this->length < j; this->length++) {
				this->item[this->length] = item[this->length];
				this->exist[this->length] = 1;
			}
			delete[] item;
			delete[] exist;
			this->size = this->length;
			return this->length; //
		}
		else {
			return 0;
		}
	}

	void _reverse() {
		CHART <ITEM> reversed;
		for (DINT i = this->length; i > 0; i--) {
			reversed << this->item[i - 1];
		}
		this->_close();
		*this = reversed;

	}

	SINT _first() {
		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i]) return i;
		}
		return -1;
	};

	SINT _open() {
		if (this->size == 0) return 0;
		for (DINT i = 0; i < this->size; i++) {
			if (this->exist[i] == 0) return i;
		}
		return -1;
	}
	void operator<<(ITEM item) {

		if (this->size == 0 || this->length == this->size) {
			//std::cout << "\n>Sizing. (" << this->size << ")";
			this->_resize();
		}
		DINT offset = this->last;
		for (DINT i = offset; i < this->size; i++) {
			if (this->exist[i] == 0) {
				this->item[i] = item;
				this->exist[i] = 1;
				this->length++;
				this->total++;
				if (i == this->last) {
					this->filled = 1;
					this->last = 0;
				}
				break;
			}
		}
	};

	void operator>>(DINT position) {

		if (this->size > 0 && this->length > 0 && position < this->size && position >= 0) {
			if (this->exist[position]) {
				ITEM item = {};
				this->exist[position] = 0;
				this->item[position] = item;
				this->length--;
			}
			if (this->filled == 1) {
				this->last = position;
				this->filled = 0;
			}
			if (this->length == 0) {
				if (this->size > 0) {
					//std::cout << "\nLength 0 & size 0, deleting.";
					delete[] this->exist;
					delete[] this->item;
					this->size = 0;
				}
			}
			//if(position < this->last) this->last = position;
		}
		else {
			std::cout << "\nOut of bounds.";
		}
	};

	ITEM& operator[](DINT position) {
		if (position >= this->size) {
			this->dummy;
		}
		return this->item[position];
	};

	void _copy(CHART<ITEM> copy) {
		if (this->length > 0) {
			delete[] this->item;
			delete[] this->exist;
		}
		this->item = new ITEM[copy.size];
		this->exist = new BINT[copy.size];
		this->length = 0;
		this->size = copy.size;
		this->total = 0;
		for (DINT i = 0; i < copy.size; i++) {
			if (copy.exist[i]) {
				this->item[this->length] = copy.item[i];
				this->exist[this->length] = 1;
				this->length++;
			}
		}

	}


	void _close() {
		if (this->size > 0) {
			delete[] this->item;
			delete[] this->exist;
			this->~CHART();
			//delete this;
		}
	}

};
template <typename ITEM>
struct ARRAY {
	ARRAY(DINT w = 0, DINT h = 0) {
		this->w = w;
		this->h = h;
		this->depth = new ARRAY<ITEM>[w];
		for (DINT x = 0; x < w; x++) {
			this->depth[x].depth = new ARRAY<ITEM>[h];
			for (DINT y = 0; y < h; y++) {
				this->depth[x].depth[y].exist = 0;
				//std::cout << "\n> Setting " << x << ", " << y << " : ";
				//std::cout << this->depth[x].exist[y];

			}
		}
	};
	DINT w, h;
	DINT length;
	ARRAY<ITEM>* depth;
	ITEM item;
	DINT exist;
	//DINT exist[w][h];


	void _add(DINT x, DINT y, ITEM item) {
		this->depth[x].depth[y].exist = 1;
		this->depth[x].depth[y].item = item;
		this->length++;
	}

	void operator <<(ITEM item) {

	}


	void _set(DINT x, DINT y, ITEM item) {
		this->depth[x].depth[y].exist = 1;
		this->depth[x].depth[y].item = item;
	}




};
struct SAVE {
	SAVE() {
	};
	~SAVE() {};

	std::fstream file;
	STRING data;
	STRING streaker;
	STRING streak;
	STRING loops;
	STRING limit;
	STRING experience;

	template <typename DATA>
	void _save(DATA data, DINT mode = 0) {
		switch (mode) {
		default:
			this->file.open("save.drx", std::ios_base::app);
			break;
		case 1:
			this->file.open("save.drx", std::fstream::out);
			break;
		}
		if (this->file.is_open()) {
			this->file << data;
			this->file << " ";
			this->file.close();
		}
	}

	void _load(DINT view = 0) {
		if (view) std::cout << "\nLoading save file: ";
		this->file.open("save.drx", std::fstream::in);
		if (this->file.is_open()) {
			char cursor;
			this->data._clear();
			while (this->file.good()) {
				this->file.get(cursor);
				this->data._add(cursor);
			}
			this->file.close();
		}
		this->streak.length = 0;
		for (DINT i = 0; this->data.text[i] != ' '; i++) {
			this->streak.text[this->streak.length] = this->data.text[i];
			this->streak.length++;
		}
		this->streak.text[this->streak.length] = '\0';
		this->streaker.length = 0;
		for (DINT i = this->streak.length + 1; this->data.text[i] != ' '; i++) {
			this->streaker.text[this->streaker.length] = this->data.text[i];
			this->streaker.length++;
		}
		this->streaker.text[this->streaker.length] = '\0';
		this->loops.length = 0;
		for (DINT i = this->streak.length + this->streaker.length + 2; this->data.text[i] != ' '; i++) {
			this->loops.text[this->loops.length] = this->data.text[i];
			this->loops.length++;
		}
		this->loops.text[this->loops.length] = '\0';
		this->experience.length = 0;
		for (DINT i = this->streak.length + this->streaker.length + this->loops.length + 3; this->data.text[i] != ' '; i++) {
			this->experience.text[this->experience.length] = this->data.text[i];
			this->experience.length++;
		}
		if (view) std::cout << this->streaker.text << " - " << this->streak.text << " " << this->loops.text << " loops.";

	}

};


struct THREAD {
	THREAD() {
		this->started = 0;
		this->working = 0;
		this->finished = 0;
		this->sleep = 1;
	};
	~THREAD() {};

	DINT started, working, finished, sleep;
	std::thread worker;

};
