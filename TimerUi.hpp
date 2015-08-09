// Folco's Metronome for SC2.
// Copyright (C) 2015  Martial Demolins AKA Folco

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMERUI_HPP
#define TIMERUI_HPP

#include <QTimer>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaPlaylist>

// Playback default volume
#define INITIAL_VOLUME 100

// ID of the radio buttons setting the termination
#define TERMINATE_ON_TRIGGER_COUNT 0
#define TERMINATE_ON_TIME_ELAPSED 1

namespace Ui
{
    class TimerUi;
}

// This class provide the interface of each timer

class TimerUi : public QWidget
{
    Q_OBJECT
  public:
    TimerUi();
    TimerUi(QString fullfilename, int period, double multiplier);
    ~TimerUi();
    void multiplierChanged(double multiplier); // Slot triggered when the time rate changes (TODO: add setMultiplier ?)
    void start();                              // Start the timer (TODO ? private ??)
    void stop();                               // Stop the timer
    void onStartAllEvent();
    QDataStream& fromStream(QDataStream& stream);
    QDataStream& toStream(QDataStream& stream) const;

  private:
    Q_DISABLE_COPY(TimerUi)
    Ui::TimerUi* ui;
    QTimer* m_timer;                 // THE timer
    double m_multiplier;             // Time rate. It's a copy of the one of the main window, to have a faster access
    QMediaContent* m_media;          // Content the sound played
    QMediaPlayer* m_player;          // The player of the sound
    QMediaPlaylist* m_playlist;      // The playlist allows to configure the player
    bool m_broken;                   // True if the media can't be played, stucking the interface
    int m_triggers;                  // -1 for unlimited timer, else the number of times the timer will be triggered
    void playMedia();                // Slot triggered when the timer expires
    void error(QMediaPlayer::Error); // Slot triggered if an error occurs
    void startAfterDelay();
    void updateVolumeLabel();
    void updatePeriodLabel();
    void hotkeyTriggered();

  private slots:
    void on_hsliderPeriod_valueChanged(int value);
    void on_hsliderVolume_valueChanged(int value);
};

QDataStream& operator<<(QDataStream& stream, const TimerUi* timerui);
QDataStream& operator>>(QDataStream& stream, TimerUi*& timerui);

#endif // TIMERUI_HPP
