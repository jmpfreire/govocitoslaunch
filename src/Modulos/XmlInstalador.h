/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlInstalador.cpp
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

#ifndef _XMLINSTALADOR_H_
	#define _XMLINSTALADOR_H_

	#include <iostream>
	#include <libxml++/libxml++.h>
	#include <glibmm/convert.h>
	#include <cstdlib>
	#include <vector>

	#include "InstaladorVersion.h"

	using namespace std;	

	class XmlInstalador : public xmlpp::SaxParser
	{
		public:
			XmlInstalador(InstaladorVersion &iv);
			~XmlInstalador();
		protected:
			//Metodos
			virtual void on_start_element(const Glib::ustring& name,
		                            const AttributeList& properties);
		    virtual void on_end_element(const Glib::ustring& name);
		    //Atributos
			string nodeName;
			string nombre, ruta;
			InstaladorVersion *punteroInstalador;
		
	};
#endif //_XMLINSTALADOR_H_