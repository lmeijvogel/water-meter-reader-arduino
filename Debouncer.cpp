class Debouncer {
  public:
    Debouncer(int maximum, bool initialState) {
      this->maximum = maximum;
      this->current = 0;
      this->isUp = initialState;
    }

    bool debounce(bool signal) {
      int delta = signal ? 1 : -1;

      current += delta;

      if (current <= 0) {
        current = 0;
        isUp = false;
      } else if (current > maximum ) {
        current = maximum;
        isUp = true;
      }

      return isUp;
    }

  private:
    int maximum;
    int current;

    bool isUp;
};
