#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vmapprequest_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vmapprequest_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vmapprequest_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMAPPREQUEST_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Encorr memory allocation error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Encorr memory allocation error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Encorr-Speicherzuweisungs-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de asignación de memoria a EnCorr.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'allocation de mémoire Encorr")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij toewijzen Encorr-geheugen")); }

        // Actions
	};
}



