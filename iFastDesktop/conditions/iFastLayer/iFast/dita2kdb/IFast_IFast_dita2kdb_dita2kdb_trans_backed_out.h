#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_trans_backed_out : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_trans_backed_out() { }
		~CIFast_IFast_dita2kdb_dita2kdb_trans_backed_out() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_TRANS_BACKED_OUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The selected profile requires AWD processing. Log on to AWD then press OK, or press CANCEL to select another profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The selected profile requires AWD processing. Log on to AWD then press OK, or press CANCEL to select another profile.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für das ausgewählte Profil ist AWD-Verarbeitung notwendig. Loggen Sie sich in AWD ein und drücken Sie OK oder drücken Sie ABBRECHEN, um ein anderes Profil auszuwählen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El perfil seleccionado requiere procesamiento de AWD. Ingrese en AWD y luego presione ACEPTAR o CANCELAR para seleccionar otro perfil.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le profil sélectionné nécessite le traitement AWD. Accédez à AWD, puis appuyez sur OK, ou sélectionnez un autre profil en appuyant sur ANNULER.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het geselecteerde profiel vereist AWD-verwerking. Meld u aan bij AWD en druk op OK, of druk op ANNULEREN om een ander profiel te selecteren")); }

        // Actions
	};
}



