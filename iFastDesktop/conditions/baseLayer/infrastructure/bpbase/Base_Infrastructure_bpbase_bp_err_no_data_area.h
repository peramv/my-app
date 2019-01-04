﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_no_data_area : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_no_data_area() { }
		~CBase_Infrastructure_bpbase_bp_err_no_data_area() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NO_DATA_AREA")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this resident state code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this resident state code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Einwohner-Staat-Code nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este código de estado de residencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code d'état/de province de résidence.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent de staatcode van deze ingezetene niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify resident state code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify resident state code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Einwohner-Staat-Code und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código de estado de residencia y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de l'état/de la province de résidence et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de staatcode van de ingezetene en voer deze opnieuw in")); }
	};
}



