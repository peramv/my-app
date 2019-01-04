#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warning_ams_allocation_change : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warning_ams_allocation_change() { }
		~CIFast_IFast_ifastcbo_err_warning_ams_allocation_change() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARNING_AMS_ALLOCATION_CHANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The allocation for AMS code %AMSCODE% has been changed.  This will affect account holders using this AMS Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Zuweisung für AMS-Code %AMSCODE% wurde geändert, dies hat Auswirkungen auf die Kontoinhaber, die diesen AMS-Code verwenden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La asignación para el código AMS %AMSCODE% se ha cambiado, afectará a los titulares de cuentas que utilizan el Código AMS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition pour le code de service de gestion de portefeuille %AMSCODE% a changé. Ce changement touchera les titulaires de comptes utilisant ce code de service de gestion de portefeuille.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De allocatie voor BBD-code %AMSCODE% is gewijzigd, dit is van invloed op de accounthouders die de BBD-code gebruiken")); }

        // Actions
	};
}



