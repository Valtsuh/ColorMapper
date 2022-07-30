
struct LIT {
	LIT(double identifier, int key, int numeric, const char upper, const char lower, LITERAL shape) {
		this->identifier = identifier;
		this->numeric = numeric;
		this->key = key;
		this->upper = upper;
		this->lower = lower;
		this->shape = shape;
	};
	LIT() {
		this->identifier = 0.0;
		this->numeric = -1;
		this->key = -1;
		this->upper = '#';
		this->lower = '#';
	}
	double identifier;
	SINT numeric, key;
	char upper, lower;
	LITERAL shape;
};

struct WRITER {
	WRITER(std::initializer_list<LIT> lts) {
		std::cout << "\nConstructing WRITER.";
		HOLDER<LIT> lits = lts;
		for (DINT i = 0; i < lits._size(); i++) {
			lit << lits[i];
		}
		//dummy = ENGINE_DUMMY;
		dummy = ENGINE_MAP_DUMMY;
	};
	static CHART <LIT> lit;
	static LIT dummy;
	static char write[16];
	static void _type(const char text[], DINT x, DINT y, DINT size = 2, DINT spacing = 2, COLOR c = B) {
		DINT px, py, ll = 0;
		LIT tmp;
		PIXEL pix;
		for (DINT length = 0; text[length] != '\0'; length++) {
			tmp = WRITER::_lit(text[length]);
			for (DINT p = 0; p < tmp.shape.pixels.length; p++) {
				pix = tmp.shape.pixels[p];
				if (pix.color.exist) {
					if (tmp.key >= 0) pix.color = c;
					px = x + (pix.x * size) + (ll * size) + (length * spacing);
					py = y + (pix.y * size);
					state._set(px, py, pix.color, size);
				}
			}
			ll += tmp.shape.size.w;
		}
	}

	static LIT _lit(const char character) {
		for (DINT i = 0; i < lit.length; i++) {
			LIT a = lit[i];
			if (a.lower == character || a.upper == character) return a;
		}
		return dummy;
	}

	static char _c(DINT n) {
		for (DINT l = n; l < WRITER::lit.length; l++) {
			if (WRITER::lit.exist[l]) {
				LIT li = WRITER::lit[l];
				if (li.numeric == n) {
					return li.upper;
				}
			}
		}
		return '?';
	}
	static char* _itc(SLINT number = -1) {
		//char write[16];
		*write = {};
		DINT length = 0;
		if (number < 0) {
			WRITER::write[0] = '-';
			number = MATH::_abs(number);
			length++;
		}
		if (number == 0) {
			write[0] = '0';
			write[1] = '\0';
		}
		else {
			CHART <DINT> digits;
			DINT count = 0;
			double t = (double)number, calc = 0.0;
			for (; t > 0.91;) {
				t = (double)(number * 0.1);
				number /= 10;
				calc = t - (double)number;
				digits << (DINT)(calc * 10);
			}
			//digits._reverse();			
			for (DINT i = digits.length - 1; i >= 0; i--) {
				write[length] = _c(digits[i]);
				length++;
			}
			write[length] = '\0';
			digits._close();
		}
		return write;
	}
};

CHART<LIT> WRITER::lit;
LIT WRITER::dummy;
char WRITER::write[16] = {};