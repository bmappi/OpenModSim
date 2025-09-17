function Controller() {
    installer.autoRejectMessageBoxes();
    installer.setMessageBoxAutomaticAnswer("Overwrite Target Directory?", QMessageBox.Yes);
    installer.installationFinished.connect(proceed);
}


function page() {
    return gui.currentPageWidget()
}


function proceed(button, delay) {
    gui.clickButton(button || buttons.NextButton, delay)
}

function logCurrentPage() {
    var pageName = page().objectName
    var pagePrettyTitle = page().title
    console.log("At page: " + pageName + " ('" + pagePrettyTitle + "')")
}

Controller.prototype.WelcomePageCallback = function() {
    logCurrentPage()
    // For some reason, delay is needed.  Two seconds seems to be enough.
    proceed(buttons.NextButton, 2000)
}

/// Just click next -- that is sign in to Qt account if credentials are
/// remembered from previous installs, or skip sign in otherwise.
Controller.prototype.CredentialsPageCallback = function() {
    logCurrentPage()
    proceed()
}

/// Skip introduction page
Controller.prototype.IntroductionPageCallback = function() {
    logCurrentPage()
    proceed()
}

Controller.prototype.TargetDirectoryPageCallback = function() {
    logCurrentPage();
    gui.currentPageWidget().TargetDirectoryLineEdit.setText("C:\\Qt\\5.6.3\\msvc2013_64");
    proceed()
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    logCurrentPage()
    // Deselect whatever was default, and can be deselected.
    page().selectAll()

    proceed()
}

/// Agree license
Controller.prototype.LicenseAgreementPageCallback = function() {
    logCurrentPage()
    page().AcceptLicenseRadioButton.checked = true
    gui.clickButton(buttons.NextButton)
}

/// Windows-specific, skip it
Controller.prototype.StartMenuDirectoryPageCallback = function() {
    logCurrentPage()
    gui.clickButton(buttons.NextButton)
}

/// Skip confirmation page
Controller.prototype.ReadyForInstallationPageCallback = function() {
    logCurrentPage()
    proceed()
}

/// Installation in progress, do nothing
Controller.prototype.PerformInstallationPageCallback = function() {
    logCurrentPage()
}


Controller.prototype.FinishedPageCallback = function() {
    logCurrentPage()
    // Deselect "launch QtCreator"
    page().RunItCheckBox.checked = false
    proceed(buttons.FinishButton)
}

/// Question for tracking usage data, refuse it
Controller.prototype.DynamicTelemetryPluginFormCallback = function() {
    logCurrentPage()
    console.log(Object.keys(page().TelemetryPluginForm.statisticGroupBox))
    var radioButtons = page().TelemetryPluginForm.statisticGroupBox
    radioButtons.disableStatisticRadioButton.checked = true
    proceed()
}