#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_vmconnect_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_vmconnect_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_vmconnect_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VMCONNECT_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Failed to find Encorr Names.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Failed to find Encorr Names.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Encorr-Namen konnten nicht gefunden werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron nombres de EnCorr.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de recherche de noms Encorr")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Encorr-namen konden niet worden gevonden")); }

        // Actions
	};
}



