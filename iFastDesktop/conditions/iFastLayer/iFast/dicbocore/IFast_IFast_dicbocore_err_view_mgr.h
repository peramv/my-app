#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_view_mgr : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_view_mgr() { }
		~CIFast_IFast_dicbocore_err_view_mgr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VIEW_MGR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum allowable PAC amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Minimum allowable PAC amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimal erlaubter PAC-Betrag für Fonds %FUNDNAME% beträgt  %AMOUNT%. Bitte geben Sie den Betrag für diesen PAC-Eintrag neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de PAC mínimo permitido para el fondo %FUNDNAME% es %AMOUNT%. Por favor vuelva a introducir el monto para este registro PAC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant minimal de PAC autorisé pour le fonds %FUNDNAME% est de %AMOUNT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegestane minimale VGC-bedrag voor fonds %FUNDNAME% is %AMOUNT%. Vul het bedrag voor dit VGC-record opnieuw in")); }

        // Actions
	};
}



