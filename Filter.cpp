class Filter {
  public:
    bool activated(bool lowState, bool highState) {
      bool result = false;

      if (highState) {
        result = wasLow;

        wasLow = false;
      } else {
        // Do not clear `wasLow` until high state was reached
        wasLow |= lowState;
      }

      return result;
    }

  private:
    bool wasLow = true;
};
