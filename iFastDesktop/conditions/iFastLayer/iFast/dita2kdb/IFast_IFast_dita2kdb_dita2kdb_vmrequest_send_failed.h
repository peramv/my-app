#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vmrequest_send_failed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vmrequest_send_failed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vmrequest_send_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMREQUEST_SEND_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Forms memory allocation error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Forms memory allocation error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Formular-Speicherzuweisungs-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de asignación de memoria a formularios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'allocation de mémoire des formulaires")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij toewijzen formuliergeheugen")); }

        // Actions
	};
}



