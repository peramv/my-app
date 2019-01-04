#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_input_fund_domestic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_input_fund_domestic() { }
		~CIFast_IFast_ifastcbo_err_input_fund_domestic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INPUT_FUND_DOMESTIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input fund must be a domestic fund for foreign content excess transfer.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Input fund must be a domestic fund for foreign content excess transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Einsatz-Fonds muss ein inländischer Fonds für Auslands-Überschuss-Transfer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo de entrada debe ser un fondo nacional para transferencia de excedente de contenido extranjero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds saisi doit être un fonds national pour le transfert d'excédent de contenu étranger.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoerfonds moet een binnenlands fonds zijn voor surplusoverdracht buitenlandse inhoud")); }

        // Actions
	};
}



