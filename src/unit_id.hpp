/*
   Copyright (C) 2008 - 2015 by David White <dave@whitevine.net>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/


#ifndef UNIT_ID_HPP_INCLUDED
#define UNIT_ID_HPP_INCLUDED

#include <ctime>

#include <boost/noncopyable.hpp>

namespace n_unit {

	struct unit_id
	{
		unit_id() : value(0) {}
		explicit unit_id(size_t val) : value(val) {}
		static const size_t highest_bit = static_cast<size_t>(1) << (sizeof(size_t) * 8 - 1);
		size_t value;

		bool is_fake() const { return (value & highest_bit) != 0; }
		bool is_empty() const { return !value; }

		static unit_id create_real(size_t val) { return unit_id(val); }
		static unit_id create_fake(size_t val) { return unit_id(val + highest_bit); }

		friend bool operator <(unit_id a, unit_id b) { return a < b; }
		friend bool operator <=(unit_id a, unit_id b) { return a <= b; }
		friend bool operator ==(unit_id a, unit_id b) { return a == b; }
		friend bool operator >=(unit_id a, unit_id b) { return a >= b; }
		friend bool operator >(unit_id a, unit_id b) { return a > b; }
	};

	class id_manager : private boost::noncopyable {
		private:
			size_t next_id_;
			size_t fake_id_;
			static id_manager manager_;
			id_manager();
		public:
			static id_manager& instance();
			/** returns id for unit that is created */
			unit_id next_id();

			unit_id next_fake_id();

			/** Used for saving id to savegame */
			size_t get_save_id();
			void set_save_id(size_t);
			/** Clears id counter after game */
			void clear();
			void reset_fake();
	};

}

#endif
