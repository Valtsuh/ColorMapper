struct DYE {
	DYE(DINT color) {
		this->value = color;
	};
	DYE() {
		this->value = 0;
	};

	SINT value;
		

	operator SINT() const {
		return this->value;
	}

	void operator=(SINT value) {
		this->value = value;
	}

	DINT _darken(SINT amount = 0) {
		return this->_clamp(this->value - amount);
	}

	DINT _lighten(SINT amount = 0) {
		return this->_clamp(this->value + amount);
	}

	DINT _clamp(SINT value) {
		if (value > 255) value = 255;
		if (value < 0) value = 0;
		return (DINT)value;
	}

	void operator+=(SINT value) {
		this->value = this->_clamp(this->value + value);
	}
	void operator-=(SINT value) {
		this->value = this->_clamp(this->value - value);
	}

};

struct COLOR {
	COLOR(DYE r = 255, DYE g = 255, DYE b = 255, DINT exist = 1, DINT brk = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = brk;
	};
	/*
	COLOR(DYE r, DYE g, DYE b, DINT exist = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->exist = exist;
		this->ref = RGB(this->r, this->g, this->b);
		this->apply = 0;
		this->brk = 0;
	}
	*/
	~COLOR() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->ref = 0;
		this->exist = 0;
	};
	DYE r, g, b;
	DINT exist, apply, brk;
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
		this->exist = color.exist;
		//this->exist = color.exist;
		this->_ref();
	}

	COLORREF _ref() {
		this->ref = RGB(this->r, this->g, this->b);
		return this->ref;
	}

	COLOR _darken(SINT amount) {

		COLOR c = { this->r._darken(amount), this->g._darken(amount), this->b._darken(amount)};
		return c;
	}

	COLOR _lighten(SINT amount) {
		COLOR c = { this->r._lighten(amount), this->g._lighten(amount), this->b._lighten(amount) };
		return c;
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

	void _dump() {
		std::cout << "\n" << "(" << this->exist << "): " << this->r << ", " << this->g << ", " << this->b;
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

		SINT calc = this->h * this->w - (y + 1) * this->w + x;
		this->pixel = (SINT*)this->memory + calc;
		*this->pixel = c.ref;

	}

	void _set(DINT px, DINT py, COLOR c = {}, DINT width = 1, DINT height = 1, DINT outline = 0, COLOR color = B) {
		
		px = this->_clamp(0, px, this->w);
		DINT tx = this->_clamp(0, px + width, this->w);
		py = this->_clamp(0, py, this->h);
		DINT ty = this->_clamp(0, py + height, this->h);
		COLOR col = c;
		for (DINT y = py; y < ty; y++) {
			SINT calc = this->h * this->w - (y + 1) * this->w + px;
			this->pixel = (SINT*)this->memory + calc;
			for (DINT x = px; x < tx; x++) {
				if (outline && (x == px || x == tx - 1 || y == py || y == ty - 1)) {
					col = color;
				} else{
					col = c;
				}
				*this->pixel = col._ref();
				this->pixel++;
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
		this->loaded = 1;
		return;
	}
	SPRITE(char filename[]) {
		std::ifstream file;
		this->facing = 0;
		this->scale = 1;
		STRING name = filename;
		name._append(".drx");
		file.open(name.text);
		if (file.is_open()) {
			CHART <char> text;
			char cursor;
			while (file.good()) {
				file.get(cursor);
				text << cursor;
			}
			text << '\0';
			//std::cout << "\nSOF(" << text.length << ")";
			for (DINT c = 2; c < text.length; c++) {
				if (text[c] == '{') {
					char exist = ' ';
					CHART <DINT> red, green, blue;
					DINT re = 0, gr = 0, bl = 0;
					DINT l = c + 1;
					COLOR color;
					do {
						red << MATH::_isnum(text[l]);
						l++;
					} while (text[l] != ',');
					red._reverse();
					for (DINT a = 0; a < red.length; a++) {
						if (a == 0) {
							re = red[a];
						}
						else {
							re += MATH::_tnth(red[a], a);
						}
					}
					red._close();
					l++;
					do {
						green << MATH::_isnum(text[l]);
						l++;
					} while (text[l] != ',');
					green._reverse();
					for (DINT b = 0; b < green.length; b++) {
						if (b == 0) {
							gr = green[b];
						}
						else {
							gr += MATH::_tnth(green[b], b);
						}
					}
					green._close();
					l++;
					do {
						blue << MATH::_isnum(text[l]);
						l++;
					} while (text[l] != ',' && text[l] != '}');

					blue._reverse();
					for (DINT c = 0; c < blue.length; c++) {
						if (c == 0) {
							bl = blue[c];
						}
						else {
							bl += MATH::_tnth(blue[c], c);
						}
					}
					blue._close();

					if (text[l] == ',') color.exist = 0; else color.exist = 1;

					color.r = re;
					color.g = gr;
					color.b = bl;
					PIXEL p;
					p.color = color;
					this->pixels << p;
					//std::cout << "\n" << r.text << " - " << g.text << " - " << b.text;
					//std::cout << "\n" << re << ", " << gr << ", " << bl;
					//std::cout << "\n" << color.r << "(" << r.text << "), " << color.g << "(" << g.text << "), " << color.b << "(" << b.text << "), " << color.exist;
					//system("pause");
				}

				if (text[c] == '}' && text[c + 1] == '}') {
					CHART <DINT> w, h;
					DINT width = 0, height = 0;
					c += 3;
					do {
						//std::cout << text[c];
						w << (DINT)MATH::_isnum(text[c]);
						c++;
					} while (text[c] != ',');
					w._reverse();
					for (DINT x = 0; x < w.length; x++) {
						if (x == 0) {
							width = w[x];
						}
						else {
							width += MATH::_tnth(w[x], x);
						}
					}
					w._close();
					//std::cout << "\nWidth: " << width;
					c += 2;
					do {
						h << (DINT)MATH::_isnum(text[c]);
						c++;
					} while (text[c] != '}');
					h._reverse();
					for (DINT y = 0; y < h.length; y++) {
						if (y == 0) {
							height = h[y];
						}
						else {
							height += MATH::_tnth(h[y], y);
						}
					}
					h._close();
					//std::cout << "\nHeight: " << height;
					this->size.w = width;
					this->size.h = height;
				}
			}
			//std::cout << "\nColors loaded: " << this->pixels.length << " (" << this->size.w << ", " << this->size.h << ")";
			//std::cout << "\nVerifying pixels.";
			DINT x = 0, y = 0;

			for (DINT p = 0; p < this->pixels.length; p++) {
				PIXEL* pix = &this->pixels[p];
				pix->x = x;
				pix->y = y;
				y++;
				if (y == this->size.h) {
					y = 0;
					x++;
				}
				//std::cout << "\n" << pix->x << ", " << pix->y << " - " << pix->color.r << ", " << pix->color.g << ", " << pix->color.b;
			}

			//std::cout << "\nEOF.";
			std::cout << "\nLoaded: " << name.text;
			this->loaded = 1;
			file.close();
		}
		else {
			std::cout << "\nFile " << filename << " doesn't exist.";
			this->loaded = 0;
		}
	}

	SPRITE() {
		this->facing = 0;
		this->scale = 1;
		this->loaded = 0;
	};
	CHART <PIXEL> pixels;
	DIMENSION size;
	DINT scale, facing, loaded;

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
						state._set(px, py, pix.color, scale, scale);
					}
				}
			}
		}
	}	
};

struct BLOCK {
	BLOCK(COLOR c = W) {
		this->color = c;
		this->num = 0;
		this->mark = 0;
	}
	COLOR color;
	DINT num, mark;
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
	COLORS(SPRITE s, DINT w = 16, DINT h = 16) {
		//SPRITE s = name;
		this->w = 0;
		this->h = 0;
		this->r = 0;
		this->c = 0;
		if (this->colors.length == 0) {
			std::cout << "\n" << s.size.w << ", " << s.size.h;
			if (s.size.w < 11 && s.size.h < 11) {
				this->_form(16, 16, X);
			}
			else {
				if (s.size.w < 18 && s.size.h < 18) {
					this->_form(24, 24, X, 14, 14);
					w = 24;
					h = 24;
				}
				else {
					this->_form(32, 32, X, 12, 12);
					w = 32;
					h = 32;
				}
			}
		}
		if (s.loaded) {
			std::cout << "\nLoading sprite into colormap";
			COLOR marker = MARKER;
			DINT x = (w - s.size.w) / 2, y = (h - s.size.h) / 2;
			for (DINT p = 0; p < s.pixels.length; p++) {
				PIXEL pix = s.pixels[p];
				DINT pixMarker = (pix.color == marker) ? (1) : (0);
				if (pix.color.exist || pixMarker) {
					BLOCK* blk = this->_nget(x + pix.x, y + pix.y);
					blk->num = p;
					blk->color._set(pix.color);
				}
			}
		}
	}
	COLORS() {
		this->w = 0;
		this->h = 0;
		this->r = 0;
		this->c = 0;
	};

	CHART<BLOCK> colors;
	BLOCK dummy;
	DINT w, h, r, c, p;
	DIMENSION measure;

	DINT _exist(COLOR color) {
		for (DINT c = 0; c < this->colors.length; c++) {
			if (this->colors[c].color == color) return 1;
		}
		return 0;
	}

	void _form(DINT w, DINT h, COLOR c, DINT width = 16, DINT height = 16, DINT padding = 1) {
		this->w = w;
		this->h = h;
		this->measure.w = w * width + w * padding;
		this->measure.h = h * height + h * padding;
		this->colors._close();
		this->p = padding;
		BLOCK blk;
		for (DINT x = 0; x < w; x++) {
			for (DINT y = 0; y < h; y++) {
				blk = { c };
				blk.num = x + 1 * y + 1;
				blk._pos(x, y, width, height, padding);
				this->colors << blk;
			}
		}
	}

	void _set(DINT x, DINT y, DINT per = 9, SINT xo = 0, SINT yo = 0, DINT w = 16, DINT h = 16, DINT p = 1) {
		this->r = 0;
		this->c = 0;
		for (DINT c = 0; c < this->colors.length; c++) {
			BLOCK* blk = &this->colors[c];
			if (c % per == 0) {
				this->r++;
				this->c = 0;
			}
			else {
				this->c++;
			}
			blk->pos.x = this->r;
			blk->pos.y = this->c;
			blk->_pos(blk->pos.x, blk->pos.y, w, h, p);
			//blk->_mea(Engine2::ENGINE::WINDOW::measure.w - blk->measure.w * this->clrs.r - this->clrs.r * 2, blk->measure.h * this->clrs.c + this->clrs.c * 2);
		}
		this->measure.w = this->c * w;
		this->measure.h = this->r * h;
	}

	void _offset(SINT xo = 0, SINT yo = 0) {
		for (DINT c = 0; c < this->colors.length; c++) {
			BLOCK* blk = &this->colors[c];
			blk->measure.x += xo;
			blk->measure.y += yo;
		}
	}

	void _generate(std::initializer_list<COLOR> clrs) {
		HOLDER<COLOR> colors = clrs;
		COLOR color;
		BLOCK blk;
		SINT sat = 15;
		for (DINT c = 0; c < colors._size(); c++) {
			color = colors[c];
			if (color.exist) {
				for (DINT l = 5; l > 1; l--) {
					blk = { color._lighten(sat * l) };
					if (this->_exist(blk.color) == 0) this->colors << blk;
				}
				blk = { color };
				if (this->_exist(blk.color) == 0) this->colors << blk;
				for (DINT d = 1; d < 7; d++) {
					blk = { color._darken(sat * d) };
					if (this->_exist(blk.color) == 0) this->colors << blk;
				}
			}
			else {
				blk = { color };
				if (this->_exist(blk.color) == 0) this->colors << blk;
			}
		}
	}

	BLOCK _get(DINT x, DINT y) {
		for (DINT b = x * y - 2; b < this->colors.length; b++) {
			if (this->colors[b].pos.x == x && this->colors[b].pos.y == y) {
				return this->colors[b];
			}
		}
		return this->dummy;
	}
	BLOCK* _nget(DINT x, DINT y) {
		for (DINT b = x * y - 2; b < this->colors.length; b++) {
			if (this->colors[b].pos.x == x && this->colors[b].pos.y == y) return &this->colors[b];
		}

		return &this->dummy;
	}
	void _adjacency(BLOCK* block, COLOR color, DINT up, DINT down, DINT left, DINT right) {
		DINT x = block->pos.x, y = block->pos.y;

		BLOCK* u = this->_nget(x, y - 1);
		BLOCK* d = this->_nget(x, y + 1);
		BLOCK* l = this->_nget(x - 1, y);
		BLOCK *r = this->_nget(x + 1, y);
		if (u->color == block->color) {
			if (y > 0) this->_adjacency(u, color, 1, 0, 1, 1);
			u->color = color;
		}
		if (d->color == block->color) {
			std::cout << "\n" << this->h;
			//if (y < this->h - 1) this->_adjacency(d, color, 0, 1, 1, 1);
			d->color = color;
		}
		if (r->color == block->color) {
			//if(x < this->w - 1) this->_adjacency(r, color, 1, 1, 0, 1);
			r->color = color;
		}
		if (l->color == block->color) {
			if (x > 0) this->_adjacency(l, color, 1, 1, 1, 0);
			l->color = color;
		}
		block->color = color;
	}

	void _color(BLOCK* center, COLOR color) {
		BLOCK* blk;
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (blk->color == center->color) blk->mark = 1; else blk->mark = 0;
		}
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (blk->mark) blk->color = color;
		}
	}

	void _darken() {
		BLOCK* blk;
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (
				blk->color.exist &&
				blk->color.r != 0 &&
				blk->color.g != 0 &&
				blk->color.b != 0
				) {
				blk->mark = 1;
			}
			else blk->mark = 0;
		}
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (blk->mark) {
				blk->color = blk->color._darken(5);
			}
		}
	}

	void _lighten() {
		BLOCK* blk;
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (
				blk->color.exist &&
				blk->color.r != 255 &&
				blk->color.g != 255 &&
				blk->color.b != 255
				) {
				blk->mark = 1;
			}
			else blk->mark = 0;
		}
		for (DINT b = 0; b < this->colors.length; b++) {
			blk = &this->colors[b];
			if (blk->mark) {
				blk->color = blk->color._lighten(5);
			}
		}
	}
};


struct PEN {
	PEN() {};

};