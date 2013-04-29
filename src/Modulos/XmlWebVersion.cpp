/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * XmlWebVersion.cpp
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

#include "XmlWebVersion.h"

/**
 Constructor
 @param &ig, referencia al vector<InstallGovocitos>.
 */
XmlWebVersion::XmlWebVersion(vector<InstallGovocitos> &ig)
{
	punteroInstall = &ig;

	instalador = new InstallGovocitos();
}

/**
 Destructor.
 */
XmlWebVersion::~XmlWebVersion()
{


}

/**
 Analiza los elementos de inicio del xml y los asigna a sus correspondientes 
 atributos.
 @param &name, const Glib::ustring del atributo de inicio del xml.
 @param &attributes, const AttributeList (array) con los atributos del xml.
 */
void XmlWebVersion::on_start_element(const Glib::ustring& name, const AttributeList& attributes)
{	
	string numVersion;
	nodeName = name;

	//Atributos
	for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		try
		{
			if("numero" == iter->name)
			{
				numVersion = iter->value;
				instalador->setUltimaVersion(UtilesLauncher::convertStringToInt(numVersion));
			}
			if("sistemaOperativo" == iter->name)
			{
				instalador->setPlataforma(iter->value);
			}
			if("path" == iter->name)
			{
				instalador->setPathXmlListado(iter->value);
			}
		}
		catch(const Glib::ConvertError& ex)
		{
			//cerr<<"XmlParse atributos Excepcion obteniendo el nombre o valor"<<ex.what()<<endl;
			cerr<<"XmlParse attributes Exception obtaining name or value"<<ex.what()<<endl;
		}
	}
}

/**
 Analiza los elementos del final del fichero xml para guardar la informacion.
 @param &name, const Glib::ustring del atributo final del xml.
 */
void XmlWebVersion::on_end_element(const Glib::ustring& name)
{
	if("version" == name)
	{
		//Añadimos el poligono al vector de poligonos
		punteroInstall->push_back(*instalador);

		delete instalador;

		instalador = new InstallGovocitos();
	}
}

