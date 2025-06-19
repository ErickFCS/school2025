import { useState } from "react";


const useInput = (initialValue: string | number, placeHolder: string | number, type: string, name: string, required: boolean) => {
    const [value, setValue] = useState<string | number>(initialValue || '');

    const onChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        setValue(event.target.value);
    };

    const reset = () => {
        setValue(initialValue || '');
    };

    return {
        value,
        setValue,
        reset,
        values: {
            placeHolder,
            type,
            onChange,
            name,
            required
        }
    };

}

export default useInput;