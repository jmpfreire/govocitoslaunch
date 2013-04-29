/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InstaladorVersion.h
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jmpintorfreire@gmail.com>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INSTALADORVERSION_H_
	#define _INSTALADORVERSION_H_

	#include <iostream>
	#include <vector>

	#include "InstallGovocitos.h"

	using namespace std;

	class InstaladorVersion : public InstallGovocitos
	{
		public:
			InstaladorVersion(int ver, string plat, string path, string desc = "");
			~InstaladorVersion();
			string getNombreFichero(int i);
			string getRutaFichero(int i);
			int getNumFicheros();
			void anadirFichero(string nombre, string ruta);
		private:
			vector<string> nombreFichero;
			vector<string> rutaFichero;
	};
#endif //_INSTALADORVERSION_H_