/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InstallGovocitos.h
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

#ifndef _INSTALLGOVOCITOS_H_
	#define _INSTALLGOVOCITOS_H_

	#include <string>

	using namespace std;

	class InstallGovocitos
	{
		public:
			InstallGovocitos();
			~InstallGovocitos();
			int getUltimaVersion();
			string getPlataforma();
			string getPathXmlListado();
			string getDescripcionActualizacion();
			void setUltimaVersion(int v);
			void setPlataforma(string p);
			void setPathXmlListado(string l);
			void setDescripcionActualizacion(string d);
		protected:
			int ultimaVersion;
			string plataforma, pathXmlListado, descripcionAct;
	};
#endif //_INSTALLGOVOCITOS_H_