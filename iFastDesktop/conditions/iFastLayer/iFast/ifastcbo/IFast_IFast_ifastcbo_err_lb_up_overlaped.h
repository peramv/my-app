#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_lb_up_overlaped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_lb_up_overlaped() { }
		~CIFast_IFast_ifastcbo_err_lb_up_overlaped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LB_UP_OVERLAPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee scale upper bound and lower bound over lapped for %SCALE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Provisionsbereich-Obergrenze und –Untergrenze überschneiden sich für  %SCALE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El límite superior e inferior de la escala de comisiones se superpone para %SCALE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les limites maximale et minimale de l'échelle de frais se sont chevauchées pour l'échelle %SCALE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bovengrens en ondergrens van de kostenschaal opverlappen voor %SCALE%")); }

        // Actions
	};
}



