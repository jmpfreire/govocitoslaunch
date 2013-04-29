/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoSeleccionAct.cpp
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

#include "DialogoSeleccionAct.h"

/**
 Constructor.
 */
DialogoSeleccionAct::DialogoSeleccionAct()
{
	InicializarGlade();

	ImageLogoG->set(UtilesLauncher::getIconoFile("logoGovocitos.png"));

	add(*vboxRelease);

	show_all();
}

/**
 Destructor.
 */
DialogoSeleccionAct::~DialogoSeleccionAct()
{

}


/**
 Devuelve un puntero del boton de update.
 @return Gtk::Button, puntero del boton update.
 */
Gtk::Button *DialogoSeleccionAct::getUpdateButton()
{
	return updateBotonG;
}

/**
 Devuelve un puntero del boton de remind later.
 @return Gtk::Button, puntero del boton remind later.
 */
Gtk::Button *DialogoSeleccionAct::getRemindLaterButton()
{
	return remindLaterG;
}

/**
 Devuelve un puntero del boton de skip version.
 @return Gtk::Button, puntero del boton skip version.
 */
Gtk::Button *DialogoSeleccionAct::getSkipVersionButton()
{
	return skipVersionG;
}

/**
 Devuelve un puntero del cuadro de texto para las notas de la version.
 @return Gtk::TextView, puntero del cuadro del dialogo con las notas.
 */
Gtk::TextView *DialogoSeleccionAct::getTextViewDescripcion()
{
	return notesVersionG;
}

/**
  Inicializa el fichero glade que contiene la interfaz diseñada del actualizador.
 */
void DialogoSeleccionAct::InicializarGlade()
{
	UtilesLauncher::getWidgetGlade(UtilesLauncher::getGladeFile("DialogoNotasActualiza.glade"), "vboxRelease", 
	               "vboxRelease", &vboxRelease,
	               "ImageLogoG", &ImageLogoG,
	               "updateBotonG", &updateBotonG,
	               "remindLaterG", &remindLaterG,
	               "skipVersionG", &skipVersionG,
	               "notesVersionG", &notesVersionG,
	               NULL);
}