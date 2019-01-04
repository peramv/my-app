﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_entity_addr_na : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_entity_addr_na() { }
		~CIFast_IFast_ifastdbrkr_err_entity_addr_na() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTITY_ADDR_NA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entity address record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entity address record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Objekt-Adresseneintrag nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de dirección de entidad no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'adresse de l'entité n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record eenheidsadres is niet beschikbaar")); }

        // Actions
	};
}



