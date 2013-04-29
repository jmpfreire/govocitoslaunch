/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlWebVersion.h
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

#ifndef _XMLWEBVERSION_H_
	#define _XMLWEBVERSION_H_

	#include <iostream>
	#include <libxml++/libxml++.h>
	#include <glibmm/convert.h>
	#include <cstdlib>
	#include <vector>

	#include "InstallGovocitos.h"
	#include "UtilesLauncher.h"

	using namespace std;

	class XmlWebVersion : public xmlpp::SaxParser
	{
		public:
			XmlWebVersion(vector<InstallGovocitos> &ig);
			~XmlWebVersion();
		protected:
			virtual void on_start_element(const Glib::ustring& name,
		                            const AttributeList& properties);
		    virtual void on_end_element(const Glib::ustring& name);
		    //Atributos
			string nodeName;			
			InstallGovocitos *instalador;
			vector<InstallGovocitos> *punteroInstall;
	};
#endif //_XMLWEBVERSION_H_