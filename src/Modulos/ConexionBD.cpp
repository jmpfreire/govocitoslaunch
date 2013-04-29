/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConexionBD.cpp
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

#include "ConexionBD.h"

/**
 Constructor, establece los datos principales del servidador de BD como son base
 de datos, url de la base de datos, usuario y contraseña.
 */
ConexionBD::ConexionBD()
{
	dataBase = "govocitos_update";
	urlDataBase = "lia.ei.uvigo.es";
	userDataBase = "root";
	passDataBase = "root";
}

/**
 Destructor.
 */
ConexionBD::~ConexionBD()
{

}

/**
 Obtiene las tablas con todos los datos de actualizaciones disponibles y selecciona
 la actualización mas reciente para el tipo de plataforma que se indica en el parametro
 plataforma.
 @param platafoma, string que contiene el tipo de sistema operativo bajo el que se
 ejecuta el actualizador.
 @param version, int contiene el numero de version actual del programa.
 @param &actualizacion, referencia al objeto InstallGovocitos que contiene los datos
 de la version a actualizar.
 @return bool, Devuelve verdadero en el caso de que se encuentre una nueva actualizacion
 y falso en caso contrario.
 */
bool ConexionBD::obtenerDatosBD(string plataforma, int version, InstallGovocitos &actualizacion)
{
	int versionBD, indice;

	indice = versionBD = 0;
	
	mysqlpp::Connection conn(false);
	
    if (conn.connect(dataBase.c_str(), urlDataBase.c_str(), userDataBase.c_str(), passDataBase.c_str()))
	{
		mysqlpp::Query query = conn.query("select * from govocitos_version");
        mysqlpp::StoreQueryResult res = query.store();
		
        // Display results
        if (res) 
		{	
            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) 
			{	
				if(versionBD < atoi(res[i]["g_version"]) && res[i]["g_plataforma"] == plataforma)
				{
					versionBD = atoi(res[i]["g_version"]);
					indice = i;
				}
            }
			if(versionBD > version)
			{
				string path;

				actualizacion.setUltimaVersion(atoi(res[indice]["g_version"]));
				actualizacion.setPlataforma((string)res[indice]["g_plataforma"]);
				actualizacion.setDescripcionActualizacion((string)res[indice]["g_descripcion"]);

				path = (string)res[indice]["g_path_fichero_xml"];
				path = path + "/" + actualizacion.getPlataforma() + "/" + UtilesLauncher::converString(actualizacion.getUltimaVersion());
				
				actualizacion.setPathXmlListado(path);

				return true;
			}
			else
			{
				return false;
			}
        }
		else 
		{
            cerr << "Failed to get item list: " << query.error() << endl;
            return false;
        }
	}
	else
	{
		cerr << "Failed to get item list: " << conn.error() << endl;
		return false;
	}
}