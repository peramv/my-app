#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_nls_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_nls_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_nls_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_NLS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Class field cannot be left blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone catégorie doit être renseignee. Veuillez sélectionner une catégorie.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Klassen-Feld muss ausgefüllt werden. Bitte wählen Sie eine Klasse.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de clase no puede dejarse en blanco. Por favor seleccione una clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Classe doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld Categorie kan niet leeg zijn. Selecteer een categorie")); }

        // Actions
	};
}



