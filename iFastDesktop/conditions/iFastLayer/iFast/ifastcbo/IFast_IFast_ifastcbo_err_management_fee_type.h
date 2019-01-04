#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_management_fee_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_management_fee_type() { }
		~CIFast_IFast_ifastcbo_err_management_fee_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MANAGEMENT_FEE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Type is not allowed for the Fee Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisionsart ist nicht für den Provisionscode erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el tipo de comisión para el código de comisión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de frais n'est pas autorisé pour le code de frais.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kostentype is niet toegestaan voor de kostencode")); }

        // Actions
	};
}



