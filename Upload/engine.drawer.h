

struct COLOR {
	COLOR(DINT r = 255, DINT g = 255, DINT b = 255, DINT exist = 1, DINT brk = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = brk;
	};
	~COLOR() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->ref = 0;
		this->exist = 0;
	};
	DINT r, g, b, exist, apply, brk;
	COLORREF ref;
	void _set(COLOR color) {
		if (color.r > 255) color.r = 255;
		if (color.r < 0) color.r = 0;
		if (color.g > 255) color.g = 255;
		if (color.g < 0) color.g = 0;
		if (color.b > 255) color.b = 255;
		if (color.b < 0) color.b = 0;
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
		//this->exist = color.exist;
		this->_ref();
	}

	COLORREF _ref() {
		this->ref = RGB(this->r, this->g, this->b);
		return this->ref;
	}

	DINT operator == (COLOR c) {
		if (this->r != c.r) return 0;
		if (this->g != c.g) return 0;
		if (this->b != c.b) return 0;
		if (this->exist != c.exist) return 0;
		return 1;
	}
	DINT operator != (COLOR c) {
		if (this->r == c.r) return 0;
		if (this->g == c.g) return 0;
		if (this->b == c.b) return 0;
		if (this->exist == c.exist) return 0;
		return 1;
	}
};

struct STATE {
	STATE() {
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->pixel = {};
		this->bi = {};
		this->memory = {};
	}
	DINT w, h, x, y;
	void* memory;
	BITMAPINFO bi;
	SINT* pixel;
	

	void _config(SINT x = -1, SINT y = -1) {
		if (this->memory) VirtualFree(this->memory, 0, MEM_RELEASE);
		this->memory = VirtualAlloc(0, this->_size(), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (x >= 0) this->x = (DINT)x;
		if (y >= 0) this->y = (DINT)y;		
		this->bi.bmiHeader.biSize = sizeof(this->bi.bmiHeader);
		//std::cout << "\nConfiguring: ";
		//std::cout << "\n" << this->w << " + " << this->x;
		//std::cout << "\n" << this->h << " + " << this->y;
		this->bi.bmiHeader.biWidth = this->w;
		this->bi.bmiHeader.biHeight = this->h;
		this->bi.bmiHeader.biPlanes = 1;
		this->bi.bmiHeader.biBitCount = 32;
		this->bi.bmiHeader.biCompression = BI_RGB;
	}

	LINT _size() {
		return this->w * this->h * sizeof(unsigned int);
	}
	

	void _position(DINT x, DINT y) {
		this->x = x;
		this->y = y;
	}

	void _precise(DINT x, DINT y, COLOR c = { 125, 25, 240 }) {
		x = this->_clamp(0, x, this->w - 1);
		y = this->_clamp(0, y, this->h - 1);
		this->pixel = (SINT*)this->memory + this->h * this->w - (y + 1) * this->w + x;
		*this->pixel = c.ref;

	}

	void _set(DINT px, DINT py, COLOR c = {}, DINT size = 1) {
		
		px = this->_clamp(0, px, this->w);
		DINT tx = this->_clamp(0, px + size, this->w);
		py = this->_clamp(0, py, this->h);
		DINT ty = this->_clamp(0, py + size, this->h);

		for (DINT y = py; y < ty; y++) {
			this->pixel = (SINT*)this->memory + this->h * this->w - (y + 1) * this->w + px;
			for (DINT x = px; x < tx; x++) {
				*this->pixel++ = c.ref;
			}
		}
	}

	void _clear(COLOR c = LGR) {
		this->pixel = (SINT*)this->memory;
		for (DINT y = 0; y < this->h; y++) {
			for (DINT x = 0; x < this->w; x++) {
				*this->pixel++ = c.ref;
				//this->_precise(x, y, c);
			}
		}
	}

	inline DINT _clamp(DINT min, DINT val, DINT max) {
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	void _draw(HWND handle) {
		HDC tool = GetDC(handle);
		StretchDIBits(tool, this->x, this->y, this->w, this->h, 0, 0, this->w, this->h, this->memory, &this->bi, DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(handle, tool);
	}

};

STATE state = {};
struct PIXEL {
	PIXEL(DINT x = 0, DINT y = 0, COLOR c = {}) {
		this->x = x;
		this->y = y;
		this->color = c;
		this->apply = 1;
	};
	COLOR color;
	DINT x, y, apply;
};
struct LITERAL {
	LITERAL(std::initializer_list<COLOR> colors, DINT width = 3, DINT height = 5) {
		HOLDER<COLOR> holder = colors;
		this->size.w = width;
		this->size.h = height;
		PIXEL pixel;
		DINT p = 0;
		//std::cout << "\n> Lettering colors. " << this->size.w << ", " << this->size.h;
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				pixel = { x, y, holder[p] };
				//std::cout << "\n> " << pixel.x << ", " << pixel.y << " (" << pixel.color.r << ", " << pixel.color.g << ", " << pixel.color.b << ")";
				this->pixels << pixel;
				p++;
			}
		}
		//std::cout << " - " << this->pixels.length;
	};
	LITERAL() {};
	~LITERAL() {};

	CHART <PIXEL> pixels;
	DIMENSION size;

	PIXEL _get(DINT x, DINT y) {
		for (DINT i = 0; i < this->pixels.size; i++) {
			if (this->pixels[i].x == x && this->pixels[i].y == y) return this->pixels[i];
		}
		PIXEL p;
		return p;
	}
};


struct SPRT {
	SPRT(std::initializer_list<COLOR> colors, SINT w = -1, SINT h = -1) {
		HOLDER<COLOR> clrs = colors;
		DINT size = 8;
		this->size.w = (w != -1) ? (w) : (size);
		this->size.h = (h != -1) ? (h) : (size);
		DINT c = 0;
		PIXEL pixel;
		this->pixels = this->size.w * this->size.h;
		for (DINT y = 0; y < this->size.h; y++) {
			for (DINT x = 0; x < this->size.w; x++) {
				pixel = { x, y, clrs[c] };
				this->pixels << pixel;
				c++;
			}
		}
	};
	SPRT() {};

	~SPRT() {};
	CHART <PIXEL> pixels;
	DIMENSION size;

	void _draw(DINT scale = 2, SINT x = -1, SINT y = -1) {
		DINT px, py;
		PIXEL pix;
		x = (x == -1) ? (this->size.x) : (x);
		y = (y == -1) ? (this->size.y) : (y);
		if (this->pixels.length > 0) {
			for (DINT p = 0; p < this->pixels.length; p++) {
				if (this->pixels.exist[p]) {
					pix = this->pixels[p];
					if (pix.color.exist) {
						px = x + pix.x * scale;
						py = y + pix.y * scale;
						state._set(px, py, pix.color, scale);
					}
				}
			}
		}
	}
};

struct RECTANGLE : SPRT {
	RECTANGLE(DINT w, DINT h, COLOR c) {
		PIXEL pi;
		this->size.w = w;
		this->size.h = h;
		for (DINT x = 0; x < w; x++) {
			for (DINT y = 0; y < h; y++) {
				pi = { x, y, c };
				this->pixels << pi;
			}
		}
	};
	RECTANGLE() {};
};

struct RCT {
	RCT(DINT x, DINT y, DINT w, DINT h, DINT fill = 1) {
		this->measure.x = x;
		this->measure.y = y;
		this->measure.w = w;
		this->measure.h = h;
		this->fill = fill;
		this->color = PNK;
	}
	RCT() {
		this->fill = 0;
	};

	DIMENSION measure;
	DINT fill;
	COLOR color;
	void _draw() {
		for (DINT x = 0; x < this->measure.w; x++) {
			for (DINT y = 0; y < this->measure.h; y++) {
				if (this->fill) {
					state._set(x + this->measure.x, y + this->measure.y, this->color);
				}
			}
		}
	}

};

struct SPRITE{
	SPRITE(std::initializer_list<COLOR> clrs, SINT w = -1, SINT h = -1) {
		HOLDER<COLOR> colors = clrs;
		DINT size = 8;
		this->size.w = (w != -1) ? (w) : (size);
		this->size.h = (h != -1) ? (h) : (size);
		DINT c = 0;
		PIXEL pixel;
		this->scale = 1;
		this->facing = 0;
		this->pixels = this->size.w * this->size.h;
		for (DINT x = 0; x < this->size.w; x++) {
			for (DINT y = 0; y < this->size.h; y++) {
				pixel = { x, y, colors[c] };
				this->pixels << pixel;
				c++;
			}
		}

		return;
	}
	SPRITE() {
		this->facing = 0;
		this->scale = 1;
	};
	CHART <PIXEL> pixels;
	DIMENSION size;
	DINT scale, facing;

	void _draw(SINT scale = -1, SINT x = -1, SINT y = -1) {
		DINT px, py;
		PIXEL pix;
		x = (x == -1) ? (this->size.x) : (x);
		y = (y == -1) ? (this->size.y) : (y);
		scale = (scale == -1) ? (this->scale) : (scale);
		if (this->pixels.length > 0) {
			for (DINT p = 0; p < this->pixels.length; p++) {
				if (this->pixels.exist[p]) {
					pix = this->pixels[p];
					if (pix.color.exist) {
						px = x + pix.x * scale;
						py = y + pix.y * scale;
						state._set(px, py, pix.color, scale);
					}
				}
			}
		}
	}	
};


struct ANM {
	ANM(std::initializer_list<SPRT> sprites) {
		HOLDER<SPRT> sprts = sprites;
		for (this->length = 0; this->length < sprts._size(); this->length++) {
			this->sprites << sprts[this->length];
		}
		this->stage = 0;
	};
	ANM() {
		this->length = 0;
		this->stage = 0;
	};
	~ANM() {};
	CHART<SPRT> sprites;
	DINT length, stage;
};


struct BLOCK {
	BLOCK(COLOR c = W) {
		this->color = c;
	}
	COLOR color;
	DINT num;
	DIMENSION measure, pos;


	void _mea(DINT x, DINT y, DINT w = 16, DINT h = 16) {
		this->measure.x = x;
		this->measure.y = y;
		this->measure.w = w;
		this->measure.h = h;
	}
	void _pos(DINT x, DINT y, DINT w = 16, DINT h = 16, DINT padding = 1) {
		this->pos.x = x;
		this->pos.y = y;
		this->measure.x = x * w + x * padding;
		this->measure.y = y * h + y * padding;
		this->measure.w = w;
		this->measure.h = h;
	};
};

struct COLORS {
	COLORS(std::initializer_list<COLOR> clrs) {
		HOLDER<COLOR> colors = clrs;
		this->w = 0;
		this->h = 0;
		this->r = 0;
		this->c = 0;
		for (DINT c = 0; c < colors._size(); c++) {
			BLOCK blk = { colors[c] };
			blk.num = c;
			blk._pos(c, c);
			this->colors << blk;
		}
	};
	/*
	COLORS(DINT w, DINT h, COLOR c, DINT size = 16) {
		for (DINT x = 0; x < w; x++) {
			for (DINT y = 0; y < h; y++) {
				BLOCK blk = { c };
				blk.num = x + 1 * y + 1;
				blk._pos(x * 16, y * 16);
				this->colors << blk;
			}
		}
	};
	*/
	COLORS() {
		this->w = 0;
		this->h = 0;
		this->r = 0;
		this->c = 0;
	};

	CHART<BLOCK> colors;
	DINT w, h, r, c;

	void _form(DINT w, DINT h, COLOR c, DINT size = 16, DINT padding = 1) {
		this->w = w;
		this->h = h;
		for (DINT x = 0; x < w; x++) {
			for (DINT y = 0; y < h; y++) {
				BLOCK blk = { c };
				blk.num = x + 1 * y + 1;
				blk._pos(x, y);
				this->colors << blk;
			}
		}
	}

	BLOCK _get(DINT x, DINT y) {
		for (DINT b = 0; b < this->colors.length; b++) {
			if (this->colors[b].pos.x == x && this->colors[b].pos.y == y) return this->colors[b];
		}
	}

};
