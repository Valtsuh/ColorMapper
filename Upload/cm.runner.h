namespace Engine2 {
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
				this->w = (this->text.length * scale) * spacing + this->p * 2;
				this->h = 5 + this->p * 2;
				this->scale = scale;
				this->spacing = spacing;
				this->x = 0;
				this->y = 0;

			}

			DINT w, h, p, x, y, scale, spacing;
			STRING text;
			BLOCK block;

			void _pos(DINT x, DINT y) {
				this->x = x;
				this->y = y;
				this->block._mea(this->x, this->y, this->w * 2 + this->p, 5 * this->scale + 4);
			}

			void _draw() {
				state._set(this->block.measure.x, this->block.measure.y, LGR, this->block.measure.w);
				WRITER::_type(this->text.text, this->x + this->p, this->y + this->p, this->scale, this->spacing, B);
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
			delete m;
			STRING title;
			title._append("Engine");
			title._space(WRITER::_itc(this->stats.fps));
			//title._space(WRITER::_c())
			SetWindowText(this->window.handle, title.wtext);

		}

		void _config() {
			this->configured = 1;
			this->on = 1;
			this->clrs = CLRS;
			DINT row = 0, col = 0, per = 9;
			for (DINT c = 0; c < this->clrs.colors.length; c++) {
				BLOCK* blk = &this->clrs.colors[c];
				if (c % per == 0) {
					this->clrs.r++;
					this->clrs.c = 0;
				}
				else {
					this->clrs.c++;
				}
				blk->_mea(Engine2::ENGINE::WINDOW::measure.w - blk->measure.w * this->clrs.r - this->clrs.r * 2, blk->measure.h * this->clrs.c + this->clrs.c * 2);
			}
			this->bg = BG;
			this->selected = X;
			this->blocks._form(16, 16, X);
			this->save = { "Save", 2 };
			this->save._pos(Engine2::ENGINE::WINDOW::measure.w - this->save.w * 2 - 10, Engine2::ENGINE::WINDOW::measure.h - 5 * this->save.scale - 10);
		}


		void _painter() {

			for (DINT b = 0; b < this->blocks.colors.length; b++) {
				BLOCK blk = this->blocks.colors[b];
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.h);
			}
			//system("pause");

			
			DIMENSION d = Engine2::ENGINE::WINDOW::measure;
			DINT w = 0;
			for (DINT c = 0; c < this->clrs.colors.length; c++){
				BLOCK blk = this->clrs.colors[c];
				if (blk.measure.x > w) w = blk.measure.x;
				state._set(blk.measure.x, blk.measure.y, blk.color, blk.measure.h);
			}

			
			this->save._draw();

			state._set(d.w - (this->clrs.r + 1) * 16 - (this->clrs.r + 1) * 2, 0, this->selected, 16);
		}

		BUTTON save;
		COLOR bg;
		COLORS blocks;
		COLORS clrs;
		STATISTICS stats;
		WINDOW window;
		DINT on, configured;
		COLOR selected;

	};
}
DIMENSION Engine2::ENGINE::WINDOW::measure;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::nf;
std::chrono::system_clock::time_point Engine2::ENGINE::STATISTICS::lf;