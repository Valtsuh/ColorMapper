
struct MATH {
	MATH() {
	};
	~MATH() {};
	static SINT _polar(SINT value) {
		return (-1) * value;
	} 

	static double _dpolar(double value = 1.0) {
		return (-1) * value;
	}

	static SINT _isnum(const char character) {
		if (character == '0') return 0;
		if (character == '1') return 1;
		if (character == '2') return 2;
		if (character == '3') return 3;
		if (character == '4') return 4;
		if (character == '5') return 5;
		if (character == '6') return 6;
		if (character == '7') return 7;
		if (character == '8') return 8;
		if (character == '9') return 9;
		return -1;

	}
	static DINT _tnth(DINT a, DINT th) {
		DINT value = a;
		do {
			value *= 10;
			th--;
		} while (th > 0);
		return value;
	}
	static SINT _gap(SINT value = 0, SINT range = -1) {
		DICE dice;
		SINT a = value - range, b = value + range;
		if (a < b) {
			return dice._roll(a, b);
		}
		else {
			return dice._roll(b, a);
		}
	}

	static DINT _iap(DINT *values = {}) {
		DINT position = 0;
		DINT value = 0;
		for (DINT p = 0; &values[position] != nullptr; p++) {
			value += values[position];
		}
		return value;

	}

	static SLINT _abs(SLINT value = -1) {
		if (value < 0) {
			value = (-1) * value;
		}
		return (SLINT)value;
	}

	static double _dabs(const double value = -1.0) {
		double val = 0.0;
		if (value < 0) {
			val = (-1.0) * value;
		}
		else {
			val = value;
		}
		return val;
	}

	static void _rotate(SPOT *p, SPOT angle) {		

		p->x = p->x * MATH::_cos(angle.z) + p->y * MATH::_sin(angle.z);
		p->y = p->x * MATH::_sin(angle.z) - p->y * MATH::_cos(angle.z);

		p->y = p->y * MATH::_cos(angle.y) - p->z * MATH::_sin(angle.y);
		p->z = p->y * MATH::_sin(angle.y) + p->z * MATH::_cos(angle.y);

		p->x = p->z * MATH::_sin(angle.x) + p->x * MATH::_cos(angle.x);
		p->z = p->z * MATH::_cos(angle.x) - p->x * MATH::_sin(angle.x);
		/*
		p->x = p->x * MATH::_cos(angle.z) + p->y * MATH::_sin(angle.z);
		p->y = p->x * MATH::_sin(angle.z) - p->y * MATH::_cos(angle.z);

		p->y = p->y * MATH::_cos(angle.y) - p->z * MATH::_sin(angle.y);
		p->z = p->y * MATH::_sin(angle.y) + p->z * MATH::_cos(angle.y);

		p->x = p->z * MATH::_sin(angle.x) + p->x * MATH::_cos(angle.x);
		p->z = p->z * MATH::_cos(angle.x) - p->x * MATH::_sin(angle.x);
		*/
	}
	static void _spec(SPOT *p, double angle) {

		p->x = (p->x * angle) / (angle + p->z);
		p->y = (p->y * angle) / (angle + p->z);

	}

	static void _change(SPOT* s, double x, double y, double z) {
		s->x += x;
		s->y += y;
		s->z += z;

		if (s->x >= 360.0) s->x -= 360.0;
		if (s->x <= -360.0) s->x += 360.0;
		if (s->y >= 360.0) s->y -= 360.0;
		if (s->y <= -360.0) s->y += 360.0;
		if (s->z >= 360.0) s->z -= 360.0;
		if (s->z <= -360.0) s->z += 360.0;
	}


	static DINT _pow(const DINT a = 1, DINT b = 2) {
		DINT value = 1;
		if (a > 0 && b > 0) {
			value = 1;
			do {
				value = a * value;
				b--;
			} while (b > 0);
		}
		return value;
	}

	static DINT _fact(const DINT a = 1) {
		DINT value = 1;
		DINT i = 1;
		do {
			value *= i;
			i++;
		} while (i <= a);
		return value;
	}

	static double _pi() {
		return 3.1415926535;
	}

	static DINT _sq(DINT number = 1) {
		return number * number;
	}

	static double _dsq(double number = 1.0) {
		if (number < 0.0) {
			return -(MATH::_dabs(number) * MATH::_dabs(number));
		}
		else {
			return number * number;
		}
	}

	template <typename a, DINT s>
	static SINT _min(a (&values)[s]) {
		SINT value = values[0];
		for (DINT i = 0; i < s; i++) {
			value = (values[i] < value) ? (values[i]) : (value);
		}

		return value;
	}

	template <typename a, DINT s>
	static SINT _max(a (&values)[s]) {

		SINT value = values[0];
		for (DINT i = 0; i < s; i++) {
			value = (values[i] > value) ? (values[i]) : (value);
		}
		return value;
	}

	static SINT _imax(INDEX<SINT> index) {
		SINT first = index._first();
		SINT value;
		if (first >= 0) {
			value = index.item[first];

			for (DINT i = first; i < index.size; i++) {
				if (index.exist[i]) value = (index.item[i] > value) ? (index.item[i]) : (value);
			}
		}
		else {
			value = 0;
		}
		return value;
	}

	static DINT _cmatch(DINT number, CHART<DINT> index) {
		for (DINT i = 0; i < index.length; i++) {
			if (index.exist[i] && index[i] == number) return 1;
		}
		return 0;
	}

	static SINT _cmax(CHART<SINT> index) {
		SINT first = index._first();
		SINT value = index[first];

		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index[i] > value) ? (index[i]) : (value);
		}
		return value;
	}

	static SINT _imin(INDEX<SINT> index) {
		DINT first = index._first();
		SINT value = index.item[first];

		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index.item[i] < value) ? (index.item[i]) : (value);
		}
		return value;
	}

	static SINT _cmin(CHART<SINT> index) {
		SINT first = index._first();
		SINT value = index[first];
		for (DINT i = first; i < index.size; i++) {
			if (index.exist[i]) value = (index[i] < value) ? (index[i]) : (value);
		}
		return value;
	}

	static double _rad(double degree = 90.0) {
		return degree * (MATH::_pi() / 180.0);
	}

	static double _length(SPOT a, SPOT b) {
		double x = MATH::_dabs(a.x - b.x);
		double y = MATH::_dabs(a.y - b.y);
		return (x > y) ? (x) : (y);

	}

	static double _side(double x1, double x2) {
		return (x1 - x2 > 0) ? (-1.0) : (1.0);
	}

	/*
	
		Study.
		
	*/

	static double _srt(double number = 2.18, double accuracy = 0.1) {
		double value = 0.0;
		double counter = 0.0, lcounter = 0.0;
		double last = 0.0;
		do {
			counter += accuracy;
			value = counter * counter;
			//std::cout << "\n" << counter << " = " << value;
			//std::cout << "\n" << MATH::_dabs(number - last) << " < " << MATH::_dabs(number - value);
			if (MATH::_dabs(number - last) < MATH::_dabs(number - value)) {
				counter = lcounter;
				break;
			}
			lcounter = counter;
			last = value;
		} while (value < number);
		//std::cout << "\nSRT: " << counter;
		return counter;
	}

	static double _sin(double angle, double accuracy = 0.0001) {
		double value, sinx, sinval, temp;
		DINT den;
		value = MATH::_rad(angle);
		temp = value;
		sinx = value;
		sinval = sin(value);
		for (DINT j = 1; accuracy <= MATH::_dabs(sinval - sinx); j++) {
			den = 2 * j * (2 * j + 1);
			temp = -temp * value * value / (double)den;
			sinx += temp;
		}
		return sinx;

	}

	static double _cos(double angle, double accuracy = 0.0001) {
		double value, temp, cosx, cosval;
		DINT den;
		value = MATH::_rad(angle);
		temp = 1.0;
		cosx = temp;
		cosval = cos(value);
		for (DINT j = 1; accuracy <= MATH::_dabs(cosval - cosx); j++) {
			den = 2 * j * (2 * j - 1);
			temp = -temp * value * value / (double)den;
			cosx += temp;
		}
		return cosx;
	}

	static double _tan(double angle) {
		return MATH::_sin(angle) / MATH::_cos(angle);

	}

	static double _ballCollision(double x1, double x2, double y1, double y2, double r1, double r2) {
		return MATH::_dabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) <= (r1 + r2) * (r1 + r2);
	};

	static double _ballDistance(double x1, double x2, double y1, double y2, double r1, double r2) {
		return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	};
};