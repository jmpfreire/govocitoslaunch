/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DescargaActualizacion.cpp
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

#include "DescargaActualizacion.h"

static time_t comienzo(0), final;
static double fraccionDesc1(0), fraccionDesc2(0);
static DialogoActulizacion *avanceDescarga;

/**
 Funcion que actualiza la barra de progreso que muestra la descarga actual de cada
 uno de los ficheros.
 @param *clientp, puntero void.
 @param dltotal, double que contiene el tamaño total de la descarga.
 @param dlnow, double que contiene el tamaño actual descargado.
 @param ultotal, double que contiene el tamaño total de la subida.
 @param ulnow, double que contiene el tamaño actual subido.
 */
int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{	
	if(avanceDescarga)
	{	
		if(comienzo && dlnow)
		{
			double tiempo, velocidad, descarga;
			
			time(&final);
			fraccionDesc2 = dlnow;

			tiempo = difftime(final, comienzo);
			
			if(tiempo >= 0.2)
			{
				descarga = fraccionDesc2 - fraccionDesc1;
				
				velocidad = (descarga/1024)/tiempo;

				avanceDescarga->actualizaVelocidad(velocidad);

				time(&comienzo);
				fraccionDesc1 = dlnow;

				avanceDescarga->actualizaInfoDescarga((dlnow/1024), (dltotal/1024));
			}
		}
		
		double percentDesc, finalizaDesc;

		UtilesLauncher::actualizarInterfaz();
	
		finalizaDesc = (dltotal - dlnow);		
		percentDesc = (dlnow/dltotal);

		if(finalizaDesc >= 0.0 && percentDesc >= 0.0)
		{
			avanceDescarga->actualizaEstado(percentDesc);
		}	
	}
	
	return 0;
}

/**
 Funcion de escritura de datos del fichero que se esta descargando.
 @param *ptr, puntero de tipo void.
 @param size, dato de tipo size_t. (tamaño total del fichero).
 @param nmemb, dato de tipo size_t. (tamaño del stream).
 @param *stream, puntero de tipo void. (stream a almacenar en el fichero).
 */
size_t writeFunction( void *ptr, size_t size, size_t nmemb, void *stream)
{
	fwrite(ptr, size, nmemb, (FILE *)stream);
    return nmemb*size;
}

/**
 Constructor.
 */
DescargaActualizacion::DescargaActualizacion()
{
	avanceDescarga = 0;
}

/**
 Destructor.
 */
DescargaActualizacion::~DescargaActualizacion()
{

}

/**
 Establece la referencia al dialogo de progreso del actualizador.
 @param &da, referencia de DialogoActulizacion.
 */
void DescargaActualizacion::setDialogoProgreso(DialogoActulizacion &da)
{
	avanceDescarga = &da;
}

/**
 Descarga los ficheros almacenados en el servidor indicados en el parametro path.
 @param path, string que contiene la direccion de los ficheros a descargar.
 @param ruta, string que contiene la ruta donde se almacenaran los ficheros descargados.
 @return bool, true si la descarga se ha realizado con exito, false en caso contrario.
 */
bool DescargaActualizacion::descargaDatos(string path, string ruta)
{	
	CURL *curl;
	CURLcode res;
	FILE *destFile;
	string pathsistema;

	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR,1);

		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		
		//Almacenando en la cache
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);

		destFile = fopen(ruta.c_str(),"wb");

		time(&comienzo);
		fraccionDesc1 = 0;
		
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &progress_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res)
		{
			return false;
		}
		
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);
		
		return true;
	}
	
	return false;
}

/**
 Descarga el fichero xml que contiene los datos de actualizacion o instalacion.
 @param path, string que contiene la ruta del servidor donde se encuentra el fichero
 xml.
 @param nombreFich, string que contiene el nombre del fichero.
 @return bool, true si la descarga se realizo con exito, false en caso contrario.
 */
bool DescargaActualizacion::descargaFicheroXml(string path, string nombreFich)
{
	CURL *curl;
	CURLcode res;
	FILE *destFile;
	string pathsistema, pathDescarga;	

	pathDescarga = path + "/" + nombreFich;
	
	curl = curl_easy_init();
	
	if(curl)
	{  
		curl_easy_setopt(curl, CURLOPT_URL, pathDescarga.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0L);  
		curl_easy_setopt(curl, CURLOPT_SSLVERSION , CURL_SSLVERSION_SSLv3);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR,1);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 2500);
		
		// Tell libcurl where to write the file
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		
		pathsistema = UtilesLauncher::direccionConfig(nombreFich);
		destFile = fopen(pathsistema.c_str(),"wb");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, destFile);

		res = curl_easy_perform(curl);

		if(res)
		{
			return false;
		}
			
		/* always cleanup */
		fclose(destFile);
		curl_easy_cleanup(curl);

		return true;
	}

	return false;
}