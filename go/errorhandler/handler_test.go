package errorhandler

import (
	"errors"
	"testing"
)

func TestError(t *testing.T) {
	defer returnError()

	err := errors.New("error occurs")
	checkError(err, "errorhandler", "TestError", "log something")
}
