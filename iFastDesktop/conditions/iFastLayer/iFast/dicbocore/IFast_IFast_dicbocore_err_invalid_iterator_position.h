#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_invalid_iterator_position : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_invalid_iterator_position() { }
		~CIFast_IFast_dicbocore_err_invalid_iterator_position() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ITERATOR_POSITION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one line of address details is required.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une ligne de details d'adresse est requise. Veuillez la saisir maintenant.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens eine Zeile der Adresse wird benötigt. Bitte geben Sie diese jetzt ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere al menos una línea de detalles de la dirección. Por favor introdúzcala ahora.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins l'une des lignes des détails de l'adresse doit être remplie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is ten minste één regel met adresdetails vereist. Vul deze nu in")); }

        // Actions
	};
}



