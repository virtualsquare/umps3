/*
 * uMPS - A general purpose computer system simulator
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>

#include "base/json.h"

int main(int argc, char** argv)
{
	JsonObject object;

	object.Set("favorite-drink", "Pan-Galactic Gargle Blaster");
	object.Set("favorite-number", 42);
	JsonArray* array = new JsonArray;
	object.Set("friends", array);
	array->Add(new JsonString("Ford Prefect"));
	array->Add(new JsonString("Trillian"));
	JsonObject* o1 = new JsonObject;
	o1->Set("name", "Marvin");
	o1->Set("manufacturer", "Sirius Cybernetics Corporation");
	array->Add(o1);

	JsonObject* nestedObject = new JsonObject;
	nestedObject->Set("true", true);
	nestedObject->Set("false", false);
	object.Set("tautologies", nestedObject);

	object.Set("What do we use to represent an empty set in JSON?", new JsonArray());
	object.Set("What does an empty object look like?", new JsonObject());

	std::string buffer;
	object.Serialize(buffer, true);
	std::cout << buffer;

	return 0;
}
