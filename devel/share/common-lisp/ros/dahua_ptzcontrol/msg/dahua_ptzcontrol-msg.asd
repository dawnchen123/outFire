
(cl:in-package :asdf)

(defsystem "dahua_ptzcontrol-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "HeatMapTemp" :depends-on ("_package_HeatMapTemp"))
    (:file "_package_HeatMapTemp" :depends-on ("_package"))
    (:file "Temperature" :depends-on ("_package_Temperature"))
    (:file "_package_Temperature" :depends-on ("_package"))
    (:file "ptz" :depends-on ("_package_ptz"))
    (:file "_package_ptz" :depends-on ("_package"))
  ))