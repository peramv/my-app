#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_dlr_not_authorized : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_dlr_not_authorized() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_dlr_not_authorized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DLR_NOT_AUTHORIZED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Return financial institution not authorized.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Return financial institution not authorized.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ausgabe des Finanzinstituts nicht autorisiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Institución financiera de retorno no autorizada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Institution financière de remboursement non autorisée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Rendement financiële instelling is niet gemachtigd")); }

        // Actions
	};
}



