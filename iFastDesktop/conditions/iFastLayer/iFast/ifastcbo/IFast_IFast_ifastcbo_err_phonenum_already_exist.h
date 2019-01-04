﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_phonenum_already_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_phonenum_already_exist() { }
		~CIFast_IFast_ifastcbo_err_phonenum_already_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PHONENUM_ALREADY_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Phone number already exist, can not be updated here.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Telefonnummer existiert bereits, kann hier nicht aktualisiert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de teléfono ya existe, no puede actualizarse aquí")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de téléphone existe déjà et ne peut être mis à jour ici.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Telefoonnummer bestaat al, kan hier niet worden bijgewerkt")); }

        // Actions
	};
}



