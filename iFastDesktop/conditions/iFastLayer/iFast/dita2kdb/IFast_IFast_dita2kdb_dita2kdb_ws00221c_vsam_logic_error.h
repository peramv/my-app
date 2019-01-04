﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_vsam_logic_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_vsam_logic_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_vsam_logic_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_VSAM_LOGIC_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Banking information has been updated since inquiry, please try again later.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Banking information has been updated since inquiry, please try again later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Seit der Anfrage wurde eine Aktualisierung der Banking-Informationen durchgeführt, bitte aktualisieren Sie und versuchen Sie es erneut.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información bancaria se ha actualizado desde la consulta, por favor vuelva a intentarlo más tarde")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire a été mise à jour depuis la requête. Veuillez réessayer plus tard.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankgegevens zijn bijgewerkt sinds de informatieaanvraag, probeer het later opnieuw")); }

        // Actions
	};
}



