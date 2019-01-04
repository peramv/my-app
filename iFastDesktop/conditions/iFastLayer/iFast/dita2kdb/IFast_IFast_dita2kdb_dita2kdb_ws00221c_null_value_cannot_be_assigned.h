#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_null_value_cannot_be_assigned : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_null_value_cannot_be_assigned() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_null_value_cannot_be_assigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_NULL_VALUE_CANNOT_BE_ASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sort by value in search request is not valid, please contact technical support.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Sort by value in search request is not valid, please contact technical support.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sortieren nach Wert in einer Suchanfrage ist nicht gültig, wenden Sie sich bitte an den technischen Support.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La opción de Ordenar por valor en la solicitud de búsqueda no es válida, por favor póngase en contacto con el soporte técnico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tri par valeur est invalide dans la demande de recherche. Veuillez communiquer avec le soutien technique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Sorteren op waarde in zoekopdracht is niet geldig, neem contact op met de technische dienst")); }

        // Actions
	};
}



