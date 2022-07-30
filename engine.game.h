struct GAME {
	GAME() {
		this->played = 0;
		this->minimap = { 3, 3 };
	};
	~GAME() {};

	struct FIGURE {
		FIGURE(const char name[] = "Undefined", const char abbr[] = "UDF") {
			this->name._write(name);
			this->abbr._write(abbr);
		}

		STRING name, abbr;
		COUNTER point;
	};

	struct CREATURE {
		CREATURE(DINT x, DINT y, SPRITE sprite, DINT scale = 2) {
			this->sprite = sprite;
			this->sprite.size.x = x;
			this->sprite.size.y = y;
			this->sprite.size.size = scale;
			this->sprite.scale = scale;
			this->move = 5;
			this->collision = -1;
			this->unique = -1;
			this->agility = { "Agility", "AGI" };
			this->agility.point._add(this->dice._roll(1, 5));
			this->strength = { "Strength", "STR" };
			this->strength.point._add(this->dice._roll(1, 5));
			this->guard = { "Guard", "GRD" };
			this->guard.point._add(this->dice._roll(1, 5));
			this->energy = { "Energy", "EGY" };
			this->energy.point.current = 0;// this->dice._roll(0, 100);
			this->energy.point.total = 100;
			this->battling = -1;
			this->id = -1;
			this->name._generate(this->dice._roll(3, 8));
			this->health._add(this->guard.point * 8);
		};
		CREATURE() {
			this->move = -1;
			this->collision = -1;
			this->unique = -1;
			this->id = -1;
			this->battling = -1;
		};
		
		STRING name;
		SPRITE sprite;
		SINT unique, id, move, collision, battling;
		COUNTER health;
		FIGURE strength, agility, guard, energy;
		DICE dice;

		void _collision(CREATURE c) {
			DIMENSION ap = this->sprite.size;
			DIMENSION bp = c.sprite.size;
			switch (this->sprite.facing) {
			case 2:
				// Down
				if (
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.y < bp.y &&
					ap.x < bp.x + (bp.w * bp.size) &&
					ap.x + (ap.w * ap.size) > bp.x
					) {
					this->collision = c.unique;
					//std::cout << "\nUp";
				}
				break;
			case 4:
				// Left
				if (
					ap.x <= bp.x + (bp.w * bp.size) &&
					ap.x + (ap.w * ap.size) > bp.x &&
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.y < bp.y + (bp.h * bp.size)
					) {
					this->collision = c.unique;
					//std::cout << "\nLeft";
				}
				break;
			case 6:
				// Right
				if (
					ap.x + (ap.w * ap.size) >= bp.x &&
					ap.x < bp.x &&
					ap.y < bp.y + (bp.h * bp.size) &&
					ap.y + (ap.h * ap.size) > bp.y
					) {
					this->collision = c.unique;
					//std::cout << "\nRight";
				}
				break;
			case 8:
				// Up
				if (
					ap.y < bp.y + (bp.h * bp.size) &&
					ap.y + (ap.h * ap.size) > bp.y &&
					ap.x + (ap.w * ap.size) > bp.x &&
					ap.x < bp.x + (bp.w * bp.size)
					) {
					this->collision = c.unique;
					//std::cout << "\nDown";
				}
				break;
			}
		}

		void _move(DINT direction) {
			switch (direction) {
			default:
				break;
			case 2:
				this->sprite.size.y = this->_clampY(this->sprite.size.y + this->move);
				this->sprite.facing = 2;
				break;
			case 4:
				this->sprite.size.x = this->_clampX(this->sprite.size.x - this->move);
				this->sprite.facing = 4;
				break;
			case 6:
				this->sprite.size.x = this->_clampX(this->sprite.size.x + this->move);
				this->sprite.facing = 6;
				break;
			case 8:
				this->sprite.size.y = this->_clampY(this->sprite.size.y - this->move);
				this->sprite.facing = 8;
				break;
			}
		}

		DINT _clampX(DINT value) {
			if (value <= GAME::MAP::measure.x) return GAME::MAP::measure.x;
			if (value >= GAME::MAP::measure.w - this->sprite.size.w * this->sprite.scale) return GAME::MAP::measure.w - this->sprite.size.w * this->sprite.scale;
			return value;
		}

		DINT _clampY(DINT value) {
			if (value <= GAME::MAP::measure.y) return GAME::MAP::measure.y;
			if (value >= GAME::MAP::measure.h - this->sprite.size.h * this->sprite.scale) return GAME::MAP::measure.h - this->sprite.size.h * this->sprite.scale;
			return value;
		}

		void _draw(DINT type, DINT px, DINT py) {
			DINT w = 5;
			DINT h = 30;
			COLOR color, sec;
			double step = 0.0, current = 0.0, c = 0.0;
			switch (type) {
			default:
				break;
			case 0:
				step = (double)this->health.total / (double)h;
				current = (double)this->health;
				sec = G;
				break;
			case 1:
				step = (double)this->energy.point.total / (double)h;
				current = (double)this->energy.point;
				sec = Y;
				break;
			case 2:
				break;
			}
			for (DINT x = 0; x < w; x++) {
				c = 0.0;
				for (DINT y = h; y >= 0; y--) {
					double s = (c + 0.01) * step;
					if (s < current) {
						color = sec;
					}
					else {
						color = R;
					}
					state._set(x + px, py - h + y, color);
					c += 0.9;
				}
			}
		}

		void _attack(CREATURE* b) {
			DINT damage = this->strength.point;// this->dice._roll(0, this->strength.point.current);
			b->health.current -= damage;
			//std::cout << "\n" << this->name.text << " attacks for " << damage << " damage (" << b->health << " / " << b->health.total << ")";
			this->energy.point = 0;
		}
	};

	struct TERRAIN {
		TERRAIN(DINT w, DINT h) {
			this->pos.w = w;
			this->pos.h = h;
			this->type = -1;
			this->scale = 1;
		}
		TERRAIN(DINT size) {
			this->pos.size = size;
			this->type = -1;
			this->scale = 1;
		}
		TERRAIN() {
			this->type = -1;
			this->scale = 1;
		};
		SINT type;
		DINT scale;
		COLOR color;
		DIMENSION pos;

		void _set() {
			state._set(MAP::measure.x + this->pos.x, MAP::measure.y + this->pos.y, this->color, this->pos.size);
		}

		void _pos(DINT x, DINT y) {
			this->pos.x = x;
			this->pos.y = y;
		}
	};
	struct MAP {
		MAP() {
			measure.x = 0;
			measure.y = 0;
			measure.w = 0;
			measure.h = 0;
		};
		struct BATTLE {
			BATTLE(CREATURE* a, CREATURE* b ) {
				this->a = a;
				this->a->battling = 1;
				this->a->energy.point.current = 0;
				this->b = b;
				this->b->battling = 1;
				this->b->energy.point.current = 0;
				this->id = -1;
				this->unique = -1;
			};
			BATTLE() {
				this->a = {};
				this->b = {};
				this->id = -1;
				this->unique = -1;
			};

			CREATURE* a, * b;
			RCT background;
			SINT id, unique;


			void _set() {
				DINT h = 30, spacing = 5, w = 100;
				this->background = { 40, (h + spacing) * this->id, w, h};
			}

			void _round() {
				CREATURE* a = this->a, * b = this->b;
				if (a->health > 0 && b->health > 0) {
					if (a->energy.point._full()) {
						a->_attack(b);
					}
					else {
						if (b->energy.point._full()) {
							b->_attack(a);
						}
					}
				}
			}

		};

		CHART <TERRAIN> terrain;
		CHART <CREATURE> creature;
		CHART <BATTLE> battle;
		DICE dice;
		static DIMENSION measure;

		void _generate(DINT w, DINT h, DINT scale = 4) {
			DINT tile = 8;
			TERRAIN t;
			for (DINT x = 0; x < w; x++) {
				for (DINT y = 0; y < h; y++) {
					t = { tile * scale };
					switch (this->dice._roll(0, 8)) {
					default:
						t.type = ENGINE_TYPE_TILE_DESOLATE;
						t.color = BRN;
						break;
					case 1:
						t.type = ENGINE_TYPE_TILE_MEADOW;
						t.color = G;
						break;
					case 3:
						t.type = ENGINE_TYPE_TILE_TEST;
						t.color = DGR;
						break;
					}
					t._pos(x * t.pos.size, y * t.pos.size);
					this->terrain << t;
				}
			}
			measure.w = w * (tile * scale);
			measure.h = h * (tile * scale);
		}

		void _pos(DINT x, DINT y) {
			measure.x = x;
			measure.w += x;
			measure.y = y;
			measure.h += y;
		}

		void _draw() {
			for (DINT t = 0; t < this->terrain.length; t++) {
				this->terrain[t]._set();
			}
		}

		void _movage() {

			for (DINT c = 0; c < this->creature.size; c++) {
				if (this->creature.exist[c]) {
					CREATURE *a = &this->creature[c];
					if (a->collision == -1 && a->battling != 1) {
						a->_move(this->dice._roll(0, 10));						
						for (DINT d = 0; d < this->creature.size; d++) {
							if (this->creature.exist[d]) {
								CREATURE *b = &this->creature[d];
								if (a->unique != b->unique && b->battling != 1) {
									a->_collision(*b);
									if (a->collision != -1) {
										b->collision = a->unique;
										BATTLE battle = { a, b };
										battle.id = this->battle._open();
										//std::cout << "\nOpen at " << battle.id;
										battle._set();
										this->battle << battle;
										//std::cout << ", battle set";
										//std::cout << " - " << a->name.text << " vs. " << b->name.text;
										break;
									}
								}
							}
						}
						
					}
				}

			}
		}

		void _battle() {
			for (DINT b = 0; b < this->battle.size; b++) {
				if (this->battle.exist[b]) {
					BATTLE* battle = &this->battle[b];
					battle->_round();
					if (battle->a->health <= 0 || battle->b->health <= 0) {
						battle->a->battling = 0;
						battle->a->collision = -1;
						battle->b->battling = 0;
						battle->b->collision = -1;
						if (battle->a->health <= 0) {
							//this->creature >> battle->a->id;
						}
						if (battle->b->health <= 0) {
							//this->creature >> battle->b->id;
						}
						this->battle >> b;
					}
				}
			}
			
		}

		void _appear(SPRITE sprite) {
			DICE d;
			CREATURE a = {0, 0, sprite };
			DINT x = d._roll(GAME::MAP::measure.x, GAME::MAP::measure.w);
			DINT y = d._roll(GAME::MAP::measure.y, GAME::MAP::measure.h);
			DINT found = 0;
			do {
				a.unique = d._roll(0, 999);
				for (DINT c = 0; c < this->creature.size; c++) {
					if (this->creature[c].unique == a.unique) found = 1;
				}
			} while (found);
			a.sprite.size.x = a._clampX(x);
			a.sprite.size.y = a._clampY(y);
			a.id = this->creature._open();
			this->creature << a;
		}

		void _clean() {

			for (DINT b = 0; b < this->battle.size; b++) {
				if (this->battle.exist[b]) {
					BATTLE ba = this->battle[b];
					if (ba.a->health <= 0 || ba.b->health <= 0) {
						this->battle >> b;
					}
				}
			}

			for (DINT c = 0; c < this->creature.size; c++) {
				if (this->creature.exist[c]) {
					CREATURE cr = this->creature[c];
					if (cr.health <= 0) {
						this->creature >> c;
					}
				}
			}

		}

		void _update() {
			for (DINT c = 0; c < this->creature.size; c++) {
				if (this->creature.exist[c]) {
					CREATURE* cr = &this->creature[c];
					if (cr->health > 0 && cr->battling) {
						if (cr->energy.point.current < cr->energy.point.total) {
							cr->energy.point.current += cr->agility.point.current + 1;
							if (cr->energy.point.current >= cr->energy.point.total) {
								cr->energy.point.current = cr->energy.point.total;
							}
						}
					}
					else {
						this->creature >> c;
					}
				}
			}
		}
	};
	struct MINIMAP {
		MINIMAP(DINT w, DINT h) {
			this->background = { w, h, DGR };
			this->background.size.size = 40;
			this->background.size.x = 0;
			this->background.size.y = 0;
		};
		MINIMAP() {};
		~MINIMAP() {};

		RECTANGLE background;

		void _pos(DINT x, DINT y) {
			this->background.size.x = x;
			this->background.size.y = y;
		}
	};


	void _draw() {
		this->minimap.background._draw(this->minimap.background.size.size);
		this->map._draw();
	}

	MAP map;
	MINIMAP minimap;
	DINT played;
	DICE dice;

	void _debug() {
		//std::cout << "\nBattles: " << this->map.battle.length;

	}

	void _config() {
	}

	void _play() {
		if (this->map.creature.length < 5) {
			SPRITE sprite;
			switch (this->dice._roll(0, 10)) {
			default:
				sprite = ENGINE_MAP_SPRITE_DUMMY;
				break;
			case 1:
				sprite = ENGINE_MAP_SPRITE_DERRIS;
				break;
			case 2:
				sprite = ENGINE_MAP_SPRITE_DEFENSE;
				break;
			case 3:
				sprite = ENGINE_MAP_SPRITE_SCYTHE;
				break;
			}


			this->map._appear(sprite);
		}
		this->_debug();
		//this->map._clean();
		this->map._battle();
		this->map._update();
		this->map._movage();

	}
};

DIMENSION GAME::MAP::measure;