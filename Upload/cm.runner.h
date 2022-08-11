namespace Engine2 {
	struct GET {
		GET(const char title[], DINT type = 1) {
			this->title = title;
			this->open = type;
			this->bg = { 25, 25, 100, 30 };
		};
		GET() {
			this->open = 0;
		};

		DINT open;
		STRING title, cin;
		DIMENSION bg;


	};
	static KEYER keyer;
	static GET input;
	struct ENGINE {
		ENGINE() {
			this->on = 0;
			this->configured = 0;
			WRITER(ENGINE_TYPOGRAPH);
		};
		using frames = std::chrono::duration<int64_t, std::ratio<1, 10>>;
		struct STATISTICS {
			STATISTICS() {
				this->fps = 0;
				Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
				//Engine2::ENGINE::STATISTICS::lf = nf - frames{ 1 };
				Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
			};

			DINT fps;
			COUNTER loops;
			TIME elapsed;
			static std::chrono::system_clock::time_point nf, lf;


			void _loop() {
				this->loops.current += 1;
				this->elapsed._increment(this->elapsed);
				if (this->loops.current > 0 && this->elapsed._since() > 0) this->fps = this->loops.current / this->elapsed._since();
			}

			void _sleep(SINT target = 60) {				
				if (target != -1 && target < 60) {
					target = 1000 / (target + target / 2);
					/*
					std::cout << "\nTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - Engine2::ENGINE::STATISTICS::lf).count() << " ms";
					std::this_thread::sleep_until(Engine2::ENGINE::STATISTICS::nf);
					Engine2::ENGINE::STATISTICS::lf = Engine2::ENGINE::STATISTICS::nf;
					Engine2::ENGINE::STATISTICS::nf += frames {1};
					*/

					Engine2::ENGINE::STATISTICS::lf = std::chrono::system_clock::now();
					std::chrono::duration<double, std::milli> work = Engine2::ENGINE::STATISTICS::lf - Engine2::ENGINE::STATISTICS::nf;
					if (work.count() < target) {
						std::chrono::duration<double, std::milli> delta_ms(target - work.count());
						auto delta_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
						std::this_thread::sleep_for(std::chrono::milliseconds(delta_duration.count()));
					}
					Engine2::ENGINE::STATISTICS::nf = std::chrono::system_clock::now();
					std::chrono::duration<double, std::milli> sleep = Engine2::ENGINE::STATISTICS::nf - Engine2::ENGINE::STATISTICS::lf;
					
					//std::cout << "\nSleep: " << (work.count() + sleep.count()) << " ms";

				}
			}

		};
		struct WINDOW {
			WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
				this->result = -1;
			};
			~WINDOW() {
				this->handle = 0;
				this->info = {};
				this->msg = { 0 };
				this->x = 0;
				this->y = 0;
				this->width = 0;
				this->heigth = 0;
				this->window = {};
				this->client = {};
			};
			HWND handle;
			WNDCLASS info;
			RECT client, window;
			DINT width, heigth, x, y;
			MSG msg;
			DIMENSION mouse;
			BOOL result;
			static DIMENSION measure;
			//TRACKMOUSEEVENT me;

			CHART<DISPLAY_DEVICE> dd;
			CHART<DEVMODE> dm;

			void _register(WNDPROC proc, HINSTANCE i, const wchar_t name[]) {
				this->info = {};
				this->info.lpfnWndProc = proc;
				this->info.hInstance = i;
				this->info.lpszClassName = name;
				this->info.hbrBackground = 0; // Note to self handle WM_ERASEBKGND [white stuck]
				this->info.hCursor = 0;
				this->info.style = 0;
				RegisterClass(&this->info);
				std::cout << "\nWindow registered. (" << GetCurrentThreadId() << ", " << GetLastError() << ")";

			};

			void _device() {

				DINT device = 0;
				BOOL devi = 0;
				DISPLAY_DEVICE dd = {};
				std::cout << "\nChecking devices.";
				do {
					devi = EnumDisplayDevicesW(NULL, device, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
					device++;
					if (devi != 0)this->dd << dd;

				} while (devi != 0);

				std::cout << "\n Devices found: ";

				for (DINT i = 0; i < this->dd.length; i++) {
					if (this->dd.exist[i]) {
						dd = this->dd[i];
						std::cout << "\n> " << dd.DeviceName;
						std::cout << " - " << dd.DeviceString;
						std::cout << " - " << dd.DeviceID;
						std::cout << " : " << *reinterpret_cast<DWORD64*>(dd.DeviceName);
						std::cout << "\n Graphics modes: ";
						BOOL got = 0;
						DINT j = 0;
						DEVMODE dev = {};
						do {
							got = EnumDisplaySettings(dd.DeviceName, j, &dev);
							std::cout << "\n>> " << dev.dmDeviceName;
							std::cout << " - " << dev.dmDriverVersion;
							std::cout << " - " << dev.dmDriverExtra;
							std::cout << " - " << dev.dmDisplayFrequency;
							if (got != 0) this->dm << dev;
						} while (got != 0);

					}
				}

			}

			HWND _set(unsigned int w, unsigned int h, unsigned int x, unsigned int y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				this->handle = CreateWindow(this->info.lpszClassName, L"Title", WS_OVERLAPPEDWINDOW, this->x, this->y, this->width, this->heigth, NULL, NULL, this->info.hInstance, NULL);
				//SetWindowLong(this->handle, GWL_STYLE, WS_BORDER);
				if (this->handle == NULL) {
					system("pause");
				}
				else {
					/*
					this->me.cbSize = sizeof(this->me);
					this->me.dwFlags = TME_HOVER;
					this->me.hwndTrack = this->handle;
					this->me.dwHoverTime = 500;
					TrackMouseEvent(&this->me);
					*/
					std::cout << "\nWindow created. (" << this->handle << ", " << GetLastError() << ")";
					this->_position(w, h, x, y);
				}
				return this->handle;
			};

			HWND _position(SINT w, SINT h, SINT x, SINT y) {
				this->x = x;
				this->y = y;
				this->width = w;
				this->heigth = h;
				SetWindowPos(this->handle, HWND_TOP, this->x, this->y, this->width, this->heigth, SWP_SHOWWINDOW);
				SendMessage(this->handle, WM_SIZE, 0, 0);
				this->_client();
				this->_window();
				//ShowWindow(this->handle, SW_SHOW);
				//UpdateWindow(this->handle);
				std::cout << "\nWindow positioned. (" << this->handle << ", " << GetLastError() << "), " << w << ", " << h;
				return this->handle;
			}

			void _client() {
				GetClientRect(this->handle, &this->client);
			}

			void _window() {
				GetWindowRect(this->handle, &this->window);
			}

		};

		struct BUTTON {
			BUTTON(const char text[] = "Undefined", DINT scale = 1, DINT spacing = 1, DINT padding = 5) {
				this->text._write(text);
				this->p = padding;
				this->measure = {0, 0, (this->text.length * 4 * scale) * spacing + this->p * 2, 5 * scale + this->p * 2 };
				this->scale = scale;
				this->mode = 0;

			};

			BUTTON(DINT scale, SPRITE sprite, DINT x, DINT y) {
				this->scale = scale;
				this->sprite = sprite;
				this->sprite.scale = scale;
				this->current = this->sprite;
				this->mode = 1;
				this->c = 0;
				this->measure = { x, y, this->sprite.size.w * scale, this->sprite.size.h * scale };
			}

			BUTTON(DINT scale, const char sprite[], DINT x, DINT y) {
				this->scale = scale;
				STRING s = sprite;
				this->sprite = s.text;
				this->sprite.scale = scale;
				this->current = this->sprite;
				STRING h = sprite;
				h._append("-hover");
				this->hover = h.text;
				this->hover.scale = scale;
				STRING a = sprite;
				a._append("-active");
				this->active = a.text;
				this->active.scale = scale;
				this->text = sprite;
				this->mode = 1;
				this->c = 0;
				this->measure = { x, y, this->sprite.size.w * scale, this->sprite.size.h * scale };
			};

			DINT mode, c, p, scale;

			STRING text;
			BLOCK block;
			SPRITE sprite, hover, active, current;
			DIMENSION measure;

			void _pos(DINT x, DINT y) {
				if(this->mode == 0) x = x - this->measure.w + this->p;
				if(this->mode == 0) y = y - this->p * 2;
				this->measure = { x, y, this->measure.w, this->measure.h };
				this->block._mea(this->measure.x, this->measure.y, this->measure.w, this->measure.h);
			}

			void _draw(SINT x = -1, SINT y = -1) {
				x = (x == -1) ? (this->measure.x) : (x);
				y = (y == -1) ? (this->measure.y) : (y);
				state._set(this->block.measure.x, this->block.measure.y, LGR, this->block.measure.w, this->block.measure.h);
				WRITER::_type(this->text.text, x + this->p, y + this->p, this->scale, 1, B);
			}


		};

		void _update() {
			POINT* m = new POINT;
			if (GetCursorPos(m)) {
				if (ScreenToClient(this->window.handle, m)) {
					m->x = (m->x < 0) ? (0) : (m->x);
					m->y = (m->y < 0) ? (0) : (m->y);
					if (this->window.mouse.x != (DINT)m->x || this->window.mouse.y != (DINT)m->y) {
						this->window.mouse.x = (DINT)m->x;
						this->window.mouse.y = (DINT)m->y;
					}
				}
			}

			if (this->test.measure._within(m->x, m->y) && this->test.c == 0) {
				this->test.current = this->test.hover;
				this->test.c = 1;
			}
			if (this->test.c == 1 && this->test.measure._within(m->x, m->y) != 1) {
				this->test.current = this->test.sprite;
				this->test.c = 0;
			}

			if (Engine2::keyer.lclick) {
				for (DINT b = 0; b < this->blocks.colors.length; b++) {
					BLOCK* blk = &this->blocks.colors[b];
					if (blk->measure._within(m->x, m->y)) {
						blk->color = this->selected;
					}
				}
			}
			if (Engine2::keyer.rclick) {
				for (DINT b = 0; b < this->blocks.colors.length; b++) {
					BLOCK* blk = &this->blocks.colors[b];
					if (blk->measure._within(m->x, m->y)) {
						blk->color = X;
					}
				}
			}
			STRING title;
			title._append("Engine");
			title._space(WRITER::_itc(this->stats.fps));

			delete m;
			SetWindowText(this->window.handle, title.wtext);

		}

		void _config() {
			this->configured = 1;
			this->on = 1;
			this->clrs._generate(COLORLIST);
			//this->clrs = CLRS;
			this->clrs._set(0, 0, 22, 0, 0, 16, 8);
			this->clrs._offset(Engine2::ENGINE::WINDOW::measure.w - this->clrs.r * 16 - this->clrs.r - 16);
			this->previous._form(1, 11, W, 16, 8);
			this->previous._offset(Engine2::ENGINE::WINDOW::measure.w - this->clrs.r * 16 - this->clrs.r * 1 - 16);
			this->bg = BG;
			this->selected = X;
			this->blocks._form(16, 16, X);

			DINT y = Engine2::ENGINE::WINDOW::measure.h - 22;
			DIMENSION e = Engine2::ENGINE::WINDOW::measure;
			this->save = {2, ENGINE_BUTTON_SAVE, Engine2::ENGINE::WINDOW::measure.w - 27, y};
			
			this->save.measure._dump();
			
			//this->save._pos();

			this->load = { 2, ENGINE_BUTTON_LOAD, e.w - 27, y - 30};			
			this->clear = { 2, ENGINE_BUTTON_CLEAR, e.w - 65, y };
			this->s = {2, ENGINE_BUTTON_SMALL, Engine2::ENGINE::WINDOW::measure.w - 160, y };
			this->m = {2, ENGINE_BUTTON_MEDIUM, Engine2::ENGINE::WINDOW::measure.w - 220, y };
			this->l = {2, ENGINE_BUTTON_LARGE, Engine2::ENGINE::WINDOW::measure.w - 280, y };
			this->test = { 2, ENGINE_BUTTON_LINE, Engine2::ENGINE::WINDOW::measure.w - 320, y };
			this->test.active = ENGINE_BUTTON_LINE_ACTIVE;
			this->test.active.scale = 2;
			this->test.hover = ENGINE_BUTTON_LINE_HOVER;
			this->test.hover.scale = 2;



			Engine2::ENGINE::preview.size = 2;
			Engine2::ENGINE::preview.y = ENGINE_PREVIEW_Y;
			Engine2::ENGINE::preview.x = Engine2::ENGINE::WINDOW::measure.w - Engine2::ENGINE::preview.size * 16 - 2;
		}


		void _painter() {

			for (DINT b = 0; b < this->blocks.colors.length; b++) {
				BLOCK blk = this->blocks.colors[b];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
			}
			for (DINT b = 0; b < this->blocks.colors.length; b++) {
				BLOCK blk = this->blocks.colors[b];
				state._set(Engine2::ENGINE::preview.x + blk.pos.x * Engine2::ENGINE::preview.size, Engine2::ENGINE::preview.y + blk.pos.y * Engine2::ENGINE::preview.size, blk.color, Engine2::ENGINE::preview.size, Engine2::ENGINE::preview.size);
			}

			
			for (DINT c = 0; c < this->clrs.colors.length; c++){
				BLOCK blk = this->clrs.colors[c];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
			}

			for (DINT p = 0; p < this->previous.colors.length; p++) {
				BLOCK blk = this->previous.colors[p];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.w, blk.measure.h);
			}

			DIMENSION d = Engine2::ENGINE::WINDOW::measure;
			state._set(d.w - (this->clrs.r + 1) * 16 - this->clrs.r - 16 - 1, 1, this->selected, 16, 16);

			this->load.current._draw(this->load.scale, this->load.measure.x, this->load.measure.y);
			this->save.current._draw(this->save.scale, this->save.measure.x, this->save.measure.y);
			this->clear.current._draw(this->clear.scale, this->clear.measure.x, this->clear.measure.y);
			this->s.current._draw(this->s.scale, this->s.measure.x, this->s.measure.y);
			this->m.current._draw(this->m.scale, this->m.measure.x, this->m.measure.y);
			this->l.current._draw(this->l.scale, this->l.measure.x, this->l.measure.y);
			this->test.current._draw(this->test.scale, this->test.measure.x, this->test.measure.y);
			if (Engine2::input.open != 0) {
				DIMENSION i = Engine2::input.bg;
				DINT scale = 1;
				DINT l = (Engine2::input.cin.length > Engine2::input.title.length) ? (Engine2::input.cin.length) : (Engine2::input.title.length);
				state._set(i.x, i.y, LGR, 200, 30);
				WRITER::_type(Engine2::input.title.text, i.x + 5, i.y + 5, scale, 1, B);
				WRITER::_type(Engine2::input.cin.text, i.x + 5, i.y + 17, scale, 1, B);
			}
		}
		static DIMENSION preview;
		BUTTON save, load, clear, s, m, l, test;
		COLOR bg;
		COLORS blocks;
		COLORS clrs;
		COLORS previous;
		STATISTICS stats;
		WINDOW window;
		DINT on, configured;
		COLOR selected;

	};
	static HWND console;
	static HWND window;
}

DIMENSION Engine2::ENGINE::preview;
DIMENSION Engine2::ENGINE::WINDOW::measure;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::nf;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::lf;