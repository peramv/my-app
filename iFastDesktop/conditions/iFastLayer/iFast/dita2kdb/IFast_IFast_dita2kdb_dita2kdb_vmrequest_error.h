#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vmrequest_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vmrequest_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vmrequest_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMREQUEST_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Encorr already loaded.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Encorr already loaded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Encorr ist bereits geladen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("EnCorr ya está cargado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Encorr a déjà été téléchargé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Encorr is al geladen")); }

        // Actions
	};
}



