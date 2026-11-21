#!/bin/python3

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget

app = QApplication([]);

window = QWidget()
window.setWindowTitle("My frist PyQT sorfware")
window.setGeometry(100, 100, 400, 300)
# window.setAttribute(Qt.WA_DeleteOnClose, True)

window.show()

app.exec_()
