#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_banktype_idnum_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_banktype_idnum_not_entered() { }
		~CIFast_IFast_ifastdbrkr_err_banktype_idnum_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANKTYPE_IDNUM_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank Type and Bank Id Num or Inst Name or Bank Id must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankart und Bank-ID oder Institutsname oder Bank-ID müssen eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben introducirse el tipo de banco y el número de identificación de banco o el nombre de la institución o la identificación del banco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de banque et le numéro de code de la banque, le nom de l'institution ou le code de la banque sont requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Banktype en Bank-ID-nummer of Instellingsnaam of Bank-ID moeten worden ingevoerd")); }

        // Actions
	};
}



