#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_default_value_used : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_default_value_used() { }
		~CIFast_IFast_dita2kdb_dita2kdb_default_value_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DEFAULT_VALUE_USED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Beneficiary record available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Beneficiary record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Begünstigten-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro de beneficiario disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de bénéficiaire disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begunstigderecord is niet beschikbaar")); }

        // Actions
	};
}



