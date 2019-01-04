#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_agree_amt : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_agree_amt() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_loi_agree_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_LOI_AGREE_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Parent/Legal Guardian, and one Designated Institution relationship per RESP Beneficiary.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only one Parent/Legal Guardian, and one Designated Institution relationship per RESP Beneficiary.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur ein Elternteil/ Vormund und eine Beziehung zum Bezeichnetem Institut pro RESP-Begünstigtem.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo un padre/tutor legal y una relación de institución designada por beneficiario RESP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul parent/tuteur légal et une seule relation avec l'institution désignée par bénéficiaire REEE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Slechts één ouder/wettelijke voogd, en één relatie voor de bestemmingsinstelling per RESP-begunstigde")); }

        // Actions
	};
}



