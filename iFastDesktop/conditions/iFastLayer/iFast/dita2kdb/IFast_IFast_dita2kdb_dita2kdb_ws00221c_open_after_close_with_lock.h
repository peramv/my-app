#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_after_close_with_lock : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_after_close_with_lock() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_open_after_close_with_lock() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_OPEN_AFTER_CLOSE_WITH_LOCK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid request: must be in persistent procedure.  Please contact technical suppport.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid request: must be in persistent procedure.  Please contact technical suppport.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Anfrage : muss in anhaltender Prozedur sein. Wenden Sie sich bitte an den technischen Support.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Solicitud no válida: debe estar en el procedimiento persistente. Por favor póngase en contacto con el soporte técnico.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Requête invalide : elle doit être en procédure continuelle. Veuillez communiquer avec le soutien technique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige opdracht: moet in vaste procedure zijn. Neem contact op met de technische dienst")); }

        // Actions
	};
}



